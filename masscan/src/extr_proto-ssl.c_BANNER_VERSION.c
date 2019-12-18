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
typedef  int /*<<< orphan*/  foo ;

/* Variables and functions */
 int /*<<< orphan*/  AUTO_LEN ; 
 int /*<<< orphan*/  PROTO_SSL3 ; 
 int /*<<< orphan*/  PROTO_VULN ; 
 int /*<<< orphan*/  banout_append (struct BannerOutput*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf_s (char*,int,char*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  strlen (char*) ; 

__attribute__((used)) static void
BANNER_VERSION(struct BannerOutput *banout, unsigned version_major,
               unsigned version_minor)
{
    char foo[64];

    switch (version_major<<8 | version_minor) {
        case 0x0300:
            banout_append(banout, PROTO_SSL3, "SSLv3 ", AUTO_LEN);
            banout_append(  banout, PROTO_VULN, "SSL[v3] ", AUTO_LEN);
            break;
        case 0x0301:
            banout_append(banout, PROTO_SSL3, "TLS/1.0 ", AUTO_LEN);
            break;
        case 0x0302:
            banout_append(banout, PROTO_SSL3, "TLS/1.1 ", AUTO_LEN);
            break;
        case 0x0303:
            banout_append(banout, PROTO_SSL3, "TLS/1.2 ", AUTO_LEN);
            break;
        case 0x0304:
            banout_append(banout, PROTO_SSL3, "TLS/1.3 ", AUTO_LEN);
            break;
        default:
            sprintf_s(foo, sizeof(foo), "SSLver[%u,%u] ", 
                      version_major,
                      version_minor);
            banout_append(banout, PROTO_SSL3, foo, strlen(foo));
    }
}