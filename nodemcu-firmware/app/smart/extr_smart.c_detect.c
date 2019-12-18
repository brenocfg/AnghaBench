#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8 ;
typedef  int uint16_t ;
typedef  int uint16 ;
struct RxControl {int dummy; } ;
typedef  int int16_t ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_5__ {int flag_match_num; int base_len; int* flag; int cur_base_seq; int base_seq_valid; int ssid_len; int pwd_len; int /*<<< orphan*/  addr; } ;
struct TYPE_4__ {int /*<<< orphan*/  password; int /*<<< orphan*/  ssid; } ;

/* Variables and functions */
 int ADDR_MAP_NUM ; 
 int /*<<< orphan*/  ADDR_MATCH_LENGTH ; 
 size_t ADDR_MATCH_START ; 
 int BASE_LENGTH ; 
 size_t BSSID_ADDR ; 
 int C_FLAG ; 
 size_t DEST_ADDR ; 
 int DS_RETRY_MASK ; 
 size_t FLAG_MATCH_NUM ; 
 int FLAG_NUM ; 
 int L_FLAG ; 
 int MAC2STR (int*) ; 
 char* MACSTR ; 
 int NIBBLE_PER_BYTE ; 
 int /*<<< orphan*/  NODE_DBG (char*,...) ; 
 int /*<<< orphan*/  NODE_ERR (char*,...) ; 
 int NO_RETRY ; 
 int PWD_FLAG ; 
 int SEP_1_INDEX ; 
 int SEP_NUM ; 
 size_t SEQ_ADDR ; 
 int SEQ_MAX ; 
 size_t SOURCE_ADDR ; 
 int SSID_FLAG ; 
 int /*<<< orphan*/  TYPE_SUBTYPE_MASK ; 
 int /*<<< orphan*/ * TYPE_SUBTYPE_QOS_DATA ; 
 int alldone ; 
 TYPE_2__** am ; 
 int* got_password ; 
 int* got_ssid ; 
 TYPE_2__* matched ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_timer_disarm (int /*<<< orphan*/ *) ; 
 int* password_nibble ; 
 scalar_t__ smart_check (int*,int,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  smart_end () ; 
 int /*<<< orphan*/  smart_timer ; 
 int* ssid_nibble ; 
 TYPE_1__* sta_conf ; 

void detect(uint8 *arg, uint16 len){
  uint16_t seq;
  int16_t seq_delta = 0;
  uint16_t byte_num = 0, bit_num = 0;
  int16_t c = 0;
  uint8 *buf = NULL;
  if( len == 12 ){
    return;
  } else if (len >= 64){
    buf = arg + sizeof(struct RxControl);
  } else {
    return;
  }
  if( ( (buf[0]) & TYPE_SUBTYPE_MASK) != TYPE_SUBTYPE_QOS_DATA){
    return;
  }
  if( (buf[1] & DS_RETRY_MASK) != NO_RETRY )
    return;
  if( buf[SEQ_ADDR] & 0xF != 0 )    // Fragment Number should = 0
    return;
  // calculate current seq number
  seq = buf[SEQ_ADDR+1];
  seq = seq<<4;
  seq += buf[SEQ_ADDR]>>4;

  if(!matched){     // cur_base_seq is ref to flag[0] when finding the patern
    int i;
    for (i = 0; i < ADDR_MAP_NUM; i++)  // for each source-dest adress pair in the map
    {
      if ( am[i]->flag_match_num == 0 ){  // not in the map yet
        if ( len - am[i]->base_len == am[i]->flag[0]) // store new source-dest adress pair to the map until flag[0] is got
        {
          // BSSID, SA, DA, store the SA, DA
          memcpy(am[i]->addr, &buf[ADDR_MATCH_START], ADDR_MATCH_LENGTH);
          am[i]->flag_match_num++;    // =1
          am[i]->cur_base_seq = seq;  // assume the first seq is found
          am[i]->base_seq_valid = 1;
          // NODE_DBG("Smart: new addr pair found\n");
        }
        break;    // break any way for the next packet to come
      }
      else if(0 == memcmp(am[i]->addr, &buf[ADDR_MATCH_START], ADDR_MATCH_LENGTH)){   // source-dest adress pair match
        if(am[i]->base_seq_valid == 0){
          if ( len - am[i]->base_len == am[i]->flag[0]) { // found the new flag[0]
            // here flag_match_num is already = 1
            am[i]->cur_base_seq = seq;
            am[i]->base_seq_valid = 1;  // the seq number is valid now
            // NODE_DBG("Smart: new base_seq found\n");
          }
          break;  // break any way for the next packet to come
        }

        // base seq number is valid, cal the delta
        if(seq >= am[i]->cur_base_seq){
          seq_delta = seq - am[i]->cur_base_seq;
        } else {
          seq_delta = SEQ_MAX - am[i]->cur_base_seq + seq;
        }

        if(seq_delta < 0){   // this should never happen
          am[i]->base_seq_valid = 0;  // the seq number is not valid
          break;
        }

        if(seq_delta == 0){   // base_seq is not valid any more
          if ( len - am[i]->base_len != am[i]->flag[0]) { // lost the flag[0]
            am[i]->base_seq_valid = 0;  // the seq number is not valid
          }
          break;  // break any way for the next packet to come
        }

        // delta is out of range, need to find the next flag[0] to start again
        if (seq_delta>=FLAG_NUM){
          am[i]->flag_match_num = 1;  // reset to 1
          if ( len - am[i]->base_len == am[i]->flag[0]) { // found the new flag[0]
            // here flag_match_num is already = 1
            am[i]->cur_base_seq = seq;
            am[i]->base_seq_valid = 1;  // the seq number is valid now
          } else {
            am[i]->base_seq_valid = 0;
          }
          break;    // done for this packet
        }

        // NODE_DBG("Smart: match_num:%d seq_delta:%d len:%d\n",am[i]->flag_match_num,seq_delta,len-am[i]->base_len);
        // seq_delta now from 1 to FLAG_NUM-1
        // flag[] == 0 ,means skip this flag.
        if ( (am[i]->flag_match_num==seq_delta) && \
          ( (am[i]->flag[am[i]->flag_match_num]==len-am[i]->base_len) || (am[i]->flag[am[i]->flag_match_num]==0) ) ){
          am[i]->flag_match_num++;
          if(am[i]->flag_match_num == FLAG_MATCH_NUM){  //every thing is match.
            NODE_ERR("Smart: got matched sender\n");
            matched = am[i];    // got the matched source-dest adress pair who is sending the udp data
            matched->base_seq_valid = 0;  // set to 0, and start to reference to the SSID_FLAG from now on
            os_timer_disarm(&smart_timer);  // note: may start a longer timeout
          }
          break;
        }

        // non match, reset, need to find next flag[0] to start again
        am[i]->flag_match_num = 1;
        am[i]->base_seq_valid = 0;
        break;
      } // non-match source-dest adress pair, continue to next pair in the map.
    } // for loop
    // break out, or loop done.
    goto end;
  } else {  // cur_base_seq is ref to SSID_FLAG when patern is alread found
    if(0 != memcmp(matched->addr, &buf[ADDR_MATCH_START], ADDR_MATCH_LENGTH)){ // source-dest adress pair not match, ignore it
      return;
    }
    if (matched->base_seq_valid == 0){  // SSID_FLAG seq invalid, need to find the next valid seq number
    // base_seq not valid, find it
      if (len - matched->base_len == SSID_FLAG){
        matched->cur_base_seq = seq;
        matched->base_seq_valid = 1;
      }
      goto end;
    }

    if(seq >= matched->cur_base_seq){
      seq_delta = seq - matched->cur_base_seq;
    } else {
      seq_delta = SEQ_MAX - matched->cur_base_seq + seq;
    }

    if(seq_delta < 0){   // this should never happen
      matched->base_seq_valid = 0;  // the seq number is not valid
      goto end;
    }

    if(seq_delta == 0){   // base_seq is not valid any more
      if ( len - matched->base_len != SSID_FLAG) { // lost the SSID_FLAG
        matched->base_seq_valid = 0;  // the seq number is not valid
      }
      goto end;  // exit for the next packet to come
    }

    if ( seq_delta > (SEP_NUM + 1)*(1+NIBBLE_PER_BYTE*matched->ssid_len) +\
      1 + (SEP_NUM + 1)*(1+NIBBLE_PER_BYTE*matched->pwd_len) ){
    // delta out of the range
      if (len - matched->base_len == SSID_FLAG){
        matched->cur_base_seq = seq;
        matched->base_seq_valid = 1;
      } else {
        matched->base_seq_valid = 0;
      }
      goto end;
    }

    // delta in the range
    if (seq_delta==1){
      int16_t ssid_len = len - matched->base_len - L_FLAG;
      if ( matched->ssid_len == 0 ){   // update the ssid_len
        if ( (ssid_len <=32) && (ssid_len >0) ){
          matched->ssid_len = ssid_len;
          NODE_DBG("Smart: found the ssid_len %d\n", matched->ssid_len);
        }
        goto end;
      }
      if (ssid_len != matched->ssid_len){  // ssid_len not match
        matched->base_seq_valid = 0;
        // note: not match, save the new one or old one? for now save the new one.
        matched->ssid_len = ssid_len;
        NODE_DBG("Smart: ssid_len not match\n");
      }
      goto end; // to the next packet
    }

    if( (SEP_NUM==2)&&(seq_delta==2 || seq_delta==3) ) {
      if (len - matched->base_len != matched->flag[seq_delta-2+SEP_1_INDEX]){  // SEP not match
        matched->base_seq_valid = 0;
        NODE_DBG("Smart: SEP-L not match\n");
      }
      goto end; // to the next packet
    }

    if( seq_delta==(SEP_NUM + 1)*(1+NIBBLE_PER_BYTE*matched->ssid_len) + 1) {
      if (len - matched->base_len != PWD_FLAG){  // PWD_FLAG not match
        matched->base_seq_valid = 0;
        NODE_DBG("Smart: PWD_FLAG not match\n");
      }
      goto end; // to the next packet
    }

    if (seq_delta==(SEP_NUM + 1)*(1+NIBBLE_PER_BYTE*matched->ssid_len) + 1 + 1){
      int16_t pwd_len = len - matched->base_len - L_FLAG;
      if ( matched->pwd_len == 0){
        if ( (pwd_len <=64) && (pwd_len>0)){
          matched->pwd_len = pwd_len;
          NODE_DBG("Smart: found the pwd_len %d\n", matched->pwd_len);
        }
        goto end; // to the next packet
      }
      if (pwd_len != matched->pwd_len){ // pwd_len not match
        matched->base_seq_valid = 0;
        // note: not match, save the new one or old one? for now save the new one.
        matched->pwd_len = pwd_len; // reset pwd_len to 0
        NODE_DBG("Smart: pwd_len not match\n");
      }
      goto end;
    }

    if (seq_delta <= (SEP_NUM + 1)*(1+NIBBLE_PER_BYTE*matched->ssid_len) ){   // in the ssid zone
      uint16_t it = (seq_delta-1-SEP_NUM-1) / (SEP_NUM + 1);  // the number of ssid nibble: 0~31 or 0~63
      uint16_t m = (seq_delta-1-SEP_NUM-1) % (SEP_NUM + 1); // 0~2
      switch(m){
        case 0: // the ssid hi/lo-nibble itself
          c = (int16_t)(len - matched->base_len - C_FLAG);
          if (c>255 || c<0){
            matched->base_seq_valid = 0;
            NODE_DBG("Smart: wrong ssid nibble\n");
            goto end;
          }
          byte_num = it / 8;  // 0~7
          bit_num = it % 8;   // 0~7
          if( (got_ssid[byte_num] & (0x1 << bit_num)) == 0){
            got_ssid[byte_num] |= 0x1 << bit_num; // set the bit
            ssid_nibble[it] = c;
          }
          break;
        case 1: // seperator 1
        case 2: // seperator 2
          if(len - matched->base_len != matched->flag[m-1+SEP_1_INDEX]){
            NODE_DBG("Smart: SEP-S not match\n");
            matched->base_seq_valid = 0;
            goto end;
          }
          break;
        default:
          break;
      }
    } else {  // in the pwd zone
      uint16_t it = (seq_delta -1 -(SEP_NUM + 1)*(1+NIBBLE_PER_BYTE*matched->ssid_len) - 2 - SEP_NUM) / (SEP_NUM + 1); // the number of pwd byte
      uint16_t m = (seq_delta -1 -(SEP_NUM + 1)*(1+NIBBLE_PER_BYTE*matched->ssid_len) - 2 - SEP_NUM) % (SEP_NUM + 1);
      switch(m){
        case 0: // the pwd hi/lo-nibble itself
          c = (int16_t)(len - matched->base_len - C_FLAG);
          if (c>255 || c<0){
            matched->base_seq_valid = 0;
            NODE_DBG("Smart: wrong password nibble\n");
            goto end;
          }
          byte_num = it / 8;  // 0~15 / 7
          bit_num = it % 8;   // 0~7
          if( (got_password[byte_num] & (0x1 << bit_num)) == 0){
            got_password[byte_num] |= 0x1 << bit_num; // set the bit
            password_nibble[it] = c;
          }
          break;
        case 1: // seperator 1
        case 2: // seperator 2
          if(len - matched->base_len != matched->flag[m-1+SEP_1_INDEX]){
            NODE_DBG("Smart: SEP-P not match\n");
            matched->base_seq_valid = 0;
            goto end;
          }
          break;
        default:
          break;
      }
    }
    // check if all done
    // NODE_DBG("Smart: ssid got %02x %02x\n", got_ssid[0], got_ssid[1]);
    // NODE_DBG("Smart: password got %02x %02x %02x\n", got_password[0], got_password[1], got_password[2]);
    int i,j;
    for(i=0;i<NIBBLE_PER_BYTE*matched->ssid_len;i++){
      byte_num = (i) / 8;
      bit_num = (i) % 8;
      if( (got_ssid[byte_num] & (0x1 << bit_num) ) != (0x1 << bit_num) ){ // check the bit == 1
        break;
      }
    }
    for(j=0;j<NIBBLE_PER_BYTE*matched->pwd_len;j++){
      byte_num = (j) / 8;
      bit_num = (j) % 8;
      if( (got_password[byte_num] & (0x1 << bit_num) ) != (0x1 << bit_num) ){ // check the 2 bit == 11
        break;
      }
    }
    if(matched->ssid_len > 0 && matched->pwd_len > 0 && i==NIBBLE_PER_BYTE*matched->ssid_len && j==NIBBLE_PER_BYTE*matched->pwd_len){    // get everything, check it.
      if( smart_check(ssid_nibble, NIBBLE_PER_BYTE*matched->ssid_len, sta_conf->ssid, got_ssid) && \
        smart_check(password_nibble, NIBBLE_PER_BYTE*matched->pwd_len, sta_conf->password, got_password) ){
        // all done
        alldone = 1;
        NODE_ERR(sta_conf->ssid);
        NODE_ERR(" %d\n", matched->ssid_len);
        NODE_ERR(sta_conf->password);
        NODE_ERR(" %d\n", matched->pwd_len);
        smart_end();
        // if(succeed){
        //   succeed(smart_succeed_arg);
        //   succeed = NULL; // reset to NULL when succeed
        //   smart_succeed_arg = NULL;
        // }
        return;
      }
    }
  }

end:
#if 0
  NODE_DBG("%d:\t0x%x 0x%x\t", len-BASE_LENGTH, buf[0],buf[1]);
  NODE_DBG(MACSTR, MAC2STR(&(buf[BSSID_ADDR])));
  NODE_DBG("\t");
  NODE_DBG(MACSTR, MAC2STR(&(buf[SOURCE_ADDR])));
  NODE_DBG("\t");
  NODE_DBG(MACSTR, MAC2STR(&(buf[DEST_ADDR])));
  uint16_t tseq = buf[SEQ_ADDR+1];
  tseq = tseq<<4;
  tseq += buf[SEQ_ADDR]>>4;
  NODE_DBG("\t0x%04x\n", tseq);
#endif
  return;
}