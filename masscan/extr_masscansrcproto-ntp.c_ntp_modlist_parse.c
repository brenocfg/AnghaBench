#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct BannerOutput {int dummy; } ;
typedef  int /*<<< orphan*/  msg ;
typedef  int /*<<< orphan*/  foo ;

/* Variables and functions */
 int /*<<< orphan*/  AUTO_LEN ; 
 int /*<<< orphan*/  PROTO_NTP ; 
 int /*<<< orphan*/  UNUSEDPARM (unsigned int*) ; 
 int /*<<< orphan*/  banout_append (struct BannerOutput*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  error_codes ; 
 int /*<<< orphan*/  sprintf_s (char*,int,char*,unsigned int,...) ; 
 char* val2string_lookup (int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void
ntp_modlist_parse(const unsigned char *px,
             unsigned length,
             struct BannerOutput *banout,
             unsigned *request_id)
{
    unsigned offset = 4;
    unsigned errcode;
    unsigned record_count;
    unsigned record_size;
 
    UNUSEDPARM(request_id);

    if (offset + 4 >= length)
        return;
    
    errcode = (px[offset]>>4)&0xF;
    record_count = (px[offset+0]&0xF) << 8 | px[offset+1];
    record_size = (px[offset+2]&0xF) << 8 | px[offset+3];

    if (errcode) {
        char foo[12];
        const char *errmsg = val2string_lookup(error_codes, errcode);
        if (errmsg == 0)
            errmsg = "Bogus Error Code";
        sprintf_s(foo, sizeof(foo), "%u", errcode);
        banout_append(banout, PROTO_NTP, "Response was NTP Error Code ", AUTO_LEN);
        banout_append(banout, PROTO_NTP, foo, AUTO_LEN);
        banout_append(banout, PROTO_NTP, " - \"", AUTO_LEN);
        banout_append(banout, PROTO_NTP, errmsg, AUTO_LEN);
        banout_append(banout, PROTO_NTP, "\"", AUTO_LEN);
        return;
    }

    if (4 + record_count * record_size > length) {
        banout_append(banout, PROTO_NTP, "response-too-big", AUTO_LEN);
        return;
    }
    if (record_count * record_size > 500) {
        banout_append(banout, PROTO_NTP, "response-too-big", AUTO_LEN);
        return;
    }

    //offset += 4;

    {
        char msg[128];

        sprintf_s(msg, sizeof(msg), " response-size=%u-bytes more=%s",
            record_count * record_size, ((px[0]>>6)&1)?"true":"false");

        banout_append(banout, PROTO_NTP, msg, AUTO_LEN);
    }
}