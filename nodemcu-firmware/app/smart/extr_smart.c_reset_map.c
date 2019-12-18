#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int cur_base_seq; void** flag; int /*<<< orphan*/  addr; scalar_t__ pwd_len; scalar_t__ ssid_len; scalar_t__ base_seq_valid; int /*<<< orphan*/  base_len; int /*<<< orphan*/  addr_len; scalar_t__ flag_match_num; } ;
typedef  TYPE_1__ smart_addr_map ;

/* Variables and functions */
 int /*<<< orphan*/  ADDR_MATCH_LENGTH ; 
 int /*<<< orphan*/  BASE_LENGTH ; 
 void* SEP_1 ; 
 int SEP_1_INDEX ; 
 void* SEP_2 ; 
 void* SSID_FLAG ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void reset_map(smart_addr_map **am, size_t num){
  int i;
  for (i = 0; i < num; ++i)
  {
    am[i]->flag_match_num = 0;
    am[i]->addr_len = ADDR_MATCH_LENGTH;
    am[i]->base_len = BASE_LENGTH;
    am[i]->cur_base_seq = -1;
    am[i]->base_seq_valid = 0;
    am[i]->ssid_len = 0;
    am[i]->pwd_len = 0;
    memset(am[i]->addr, 0, ADDR_MATCH_LENGTH);
    if(SEP_1_INDEX==0){
      am[i]->flag[0] = SEP_1;
      am[i]->flag[1] = SEP_2;
      am[i]->flag[2] = SSID_FLAG;
    }
    if(SEP_1_INDEX==2){
      am[i]->flag[0] = SSID_FLAG;
      am[i]->flag[1] = 0; // skip this flag
      am[i]->flag[2] = SEP_1;
      am[i]->flag[3] = SEP_2;
    }
  }
}