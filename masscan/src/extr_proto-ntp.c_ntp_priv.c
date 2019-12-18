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

/* Variables and functions */
 int /*<<< orphan*/  PROTO_NTP ; 
 int /*<<< orphan*/  banout_append (struct BannerOutput*,int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  ntp_modlist_parse (unsigned char const*,unsigned int,struct BannerOutput*,unsigned int*) ; 
 int /*<<< orphan*/  request_codes ; 
 int strlen (char const*) ; 
 char* val2string_lookup (int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void
ntp_priv(const unsigned char *px,
             unsigned length,
             struct BannerOutput *banout,
             unsigned *request_id)
{
    unsigned implementation = px[2];
    unsigned request_code = px[3];
    const char *request_string;
    
    switch (implementation) {
        case 0: banout_append(banout, PROTO_NTP, "UNIV", 4); return;
        case 2: banout_append(banout, PROTO_NTP, "XNTPD-OLD", 9); return;
        case 3: banout_append(banout, PROTO_NTP, "XNTPD", 5); break;
        default:
            return;
    }
    
    request_string = val2string_lookup(request_codes, request_code);
    if (request_string) {
        banout_append(banout, PROTO_NTP, " ", 1);
        banout_append(banout, PROTO_NTP, request_string, strlen(request_string));
    }
    
    switch (request_code) {
        case 42:
            ntp_modlist_parse(px, length, banout, request_id);
            break;
    }    
    
}