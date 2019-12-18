#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tcb_state ;
struct ProtocolState {int dummy; } ;
struct InteractiveData {int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct BannerOutput {int dummy; } ;
struct Banner1 {int dummy; } ;
struct TYPE_10__ {int (* selftest ) () ;} ;
struct TYPE_9__ {int (* selftest ) () ;} ;
struct TYPE_8__ {int (* selftest ) () ;} ;
struct TYPE_7__ {int (* selftest ) () ;} ;
struct TYPE_6__ {int (* selftest ) () ;} ;

/* Variables and functions */
 int /*<<< orphan*/  PROTO_HTTP ; 
 struct Banner1* banner1_create () ; 
 int /*<<< orphan*/  banner1_destroy (struct Banner1*) ; 
 int /*<<< orphan*/  banner1_parse (struct Banner1*,struct ProtocolState*,unsigned char const*,unsigned int,struct BannerOutput*,struct InteractiveData*) ; 
 TYPE_5__ banner_http ; 
 TYPE_4__ banner_rdp ; 
 TYPE_3__ banner_smb1 ; 
 TYPE_2__ banner_ssl ; 
 TYPE_1__ banner_telnet ; 
 int /*<<< orphan*/  banout_init (struct BannerOutput*) ; 
 int /*<<< orphan*/  banout_release (struct BannerOutput*) ; 
 scalar_t__ banout_selftest () ; 
 unsigned char* banout_string (struct BannerOutput*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ memcmp (unsigned char const*,char*,int) ; 
 int /*<<< orphan*/  memset (struct ProtocolState*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strlen (char const*) ; 
 int stub1 () ; 
 int stub2 () ; 
 int stub3 () ; 
 int stub4 () ; 
 int stub5 () ; 

int
banner1_selftest()
{
    unsigned i;
    struct Banner1 *b;
    struct ProtocolState tcb_state[1];
    const unsigned char *px;
    unsigned length;
    struct BannerOutput banout[1];
    static const char *http_header =
        "HTTP/1.0 302 Redirect\r\n"
        "Date: Tue, 03 Sep 2013 06:50:01 GMT\r\n"
        "Connection: close\r\n"
        "Via: HTTP/1.1 ir14.fp.bf1.yahoo.com (YahooTrafficServer/1.2.0.13 [c s f ])\r\n"
        "Server: YTS/1.20.13\r\n"
        "Cache-Control: no-store\r\n"
        "Content-Type: text/html\r\n"
        "Content-Language: en\r\n"
        "Location: http://failsafe.fp.yahoo.com/404.html\r\n"
        "Content-Length: 227\r\n"
        "\r\n<title>hello</title>\n";
    px = (const unsigned char *)http_header;
    length = (unsigned)strlen(http_header);


    /*
     * First, test the "banout" subsystem
     */
    if (banout_selftest() != 0) {
        fprintf(stderr, "banout: failed\n");
        return 1;
    }


    /*
     * Test one character at a time
     */
    b = banner1_create();
    banout_init(banout);

    memset(tcb_state, 0, sizeof(tcb_state[0]));

    for (i=0; i<length; i++) {
        struct InteractiveData more = {0,0};

        banner1_parse(
                    b,
                    tcb_state,
                    px+i, 1,
                    banout,
                    &more);
    }


    {
        const unsigned char *s = banout_string(banout, PROTO_HTTP);
        if (memcmp(s, "HTTP/1.0 302", 11) != 0) {
            printf("banner1: test failed\n");
            return 1;
        }
    }
    banout_release(banout);
    banner1_destroy(b);

    /*
     * Test whole buffer
     */
    b = banner1_create();

    memset(tcb_state, 0, sizeof(tcb_state[0]));

    banner1_parse(
                    b,
                    tcb_state,
                    px, length,
                    banout,
                    0);
    banner1_destroy(b);
    /*if (memcmp(banner, "Via:HTTP/1.1", 11) != 0) {
        printf("banner1: test failed\n");
        return 1;
    }*/


    {
        int x = 0;

        x = banner_ssl.selftest();
        if (x) {
            fprintf(stderr, "SSL banner: selftest failed\n");
            return 1;
        }
        
        x = banner_smb1.selftest();
        if (x) {
            fprintf(stderr, "SMB banner: selftest failed\n");
            return 1;
        }
        
        x = banner_http.selftest();
        if (x) {
            fprintf(stderr, "HTTP banner: selftest failed\n");
            return 1;
        }
        
        x = banner_telnet.selftest();
        if (x) {
            fprintf(stderr, "Telnet banner: selftest failed\n");
            return 1;
        }
        
        x = banner_rdp.selftest();
        if (x) {
            fprintf(stderr, "RDP banner: selftest failed\n");
            return 1;
        }
        
        return x;
    }
}