#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct TCP_ConnectionTable {unsigned int timeout_connection; unsigned int timeout_hello; struct Banner1* banner1; } ;
struct ProtocolParserStream {char* name; void* hello; void* hello_length; } ;
struct TYPE_2__ {struct ProtocolParserStream** tcp; } ;
struct Banner1 {int is_heartbleed; int is_ticketbleed; int is_poodle_sslv3; TYPE_1__ payloads; } ;

/* Variables and functions */
 struct ProtocolParserStream* CALLOC (int,int) ; 
 int /*<<< orphan*/  LOG (int,char*,...) ; 
 void* MALLOC (size_t) ; 
 struct ProtocolParserStream banner_http ; 
 int /*<<< orphan*/  banner_smb1 ; 
 struct ProtocolParserStream banner_ssl ; 
 void* base64_decode (char*,size_t,void const*,size_t) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*) ; 
 void* http_change_field (unsigned char**,unsigned int,char*,unsigned char const*,unsigned int) ; 
 scalar_t__ name_equals (char const*,char*) ; 
 scalar_t__ parseInt (void const*,size_t) ; 
 int /*<<< orphan*/  smb_set_hello_v1 (int /*<<< orphan*/ *) ; 
 void* ssl_add_cipherspec (void*,int,int) ; 
 void* ssl_hello (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ssl_hello_heartbeat_template ; 
 void* ssl_hello_size (void*) ; 
 int /*<<< orphan*/  ssl_hello_sslv3_template ; 
 int /*<<< orphan*/  ssl_hello_ticketbleed_template ; 
 int /*<<< orphan*/  stderr ; 
 char* strchr (char const*,char) ; 
 scalar_t__ strtoul (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
tcpcon_set_parameter(struct TCP_ConnectionTable *tcpcon,
                        const char *name,
                        size_t value_length,
                        const void *value)
{
    struct Banner1 *banner1 = tcpcon->banner1;

    /*
     * You can reset your user-agent here. Whenever I do a scan, I always
     * reset my user-agent. That's now you know it's not me scanning
     * you on the open Internet -- I would never use the default user-agent
     * string built into masscan
     */
    if (name_equals(name, "http-user-agent")) {
        banner_http.hello_length = http_change_field(
                                (unsigned char**)&banner_http.hello,
                                (unsigned)banner_http.hello_length,
                                "User-Agent:",
                                (const unsigned char *)value,
                                (unsigned)value_length);
        return;
    }

    if (name_equals(name, "timeout") || name_equals(name, "connection-timeout")) {
        uint64_t n = parseInt(value, value_length);
        tcpcon->timeout_connection = (unsigned)n;
        LOG(1, "TCP connection-timeout = %u\n", tcpcon->timeout_connection);
        return;
    }
    if (name_equals(name, "hello-timeout")) {
        uint64_t n = parseInt(value, value_length);
        tcpcon->timeout_hello = (unsigned)n;
        LOG(1, "TCP hello-timeout = \"%.*s\"\n", (int)value_length, (const char *)value);
        LOG(1, "TCP hello-timeout = %u\n", (unsigned)tcpcon->timeout_hello);
        return;
    }

    /*
     * Force SSL processing on all ports
     */
    if (name_equals(name, "hello") && name_equals(value, "ssl")) {
        unsigned i;
        
        LOG(2, "HELLO: setting SSL hello message\n");
        for (i=0; i<65535; i++) {
            banner1->payloads.tcp[i] = &banner_ssl;
        }
        
        return;
    }
    
    /*
     * Force HTTP processing on all ports
     */
    if (name_equals(name, "hello") && name_equals(value, "http")) {
        unsigned i;
        
        LOG(2, "HELLO: setting HTTP hello message\n");
        for (i=0; i<65535; i++) {
            banner1->payloads.tcp[i] = &banner_http;
        }
        
        return;
    }
    
    /*
     * Downgrade SMB hello from v1/v2 to use only v1
     */
    if (name_equals(name, "hello") && name_equals(value, "smbv1")) {
        smb_set_hello_v1(&banner_smb1);        
        return;
    }

    /*
     * 2014-04-08: scan for Neel Mehta's "heartbleed" bug
     */
    if (name_equals(name, "heartbleed")) {
        unsigned i;

        /* Change the hello message to including negotiating the use of 
         * the "heartbeat" extension */
        banner_ssl.hello = ssl_hello(ssl_hello_heartbeat_template);
        banner_ssl.hello_length = ssl_hello_size(banner_ssl.hello);
        tcpcon->banner1->is_heartbleed = 1;

        for (i=0; i<65535; i++) {
            banner1->payloads.tcp[i] = &banner_ssl;
        }

        return;
    }

    if (name_equals(name, "ticketbleed")) {
        unsigned i;

        /* Change the hello message to including negotiating the use of 
         * the "heartbeat" extension */
        banner_ssl.hello = ssl_hello(ssl_hello_ticketbleed_template);
        banner_ssl.hello_length = ssl_hello_size(banner_ssl.hello);
        tcpcon->banner1->is_ticketbleed = 1;

        for (i=0; i<65535; i++) {
            banner1->payloads.tcp[i] = &banner_ssl;
        }

        return;
    }

    /*
     * 2014-10-16: scan for SSLv3 servers (POODLE)
     */
    if (name_equals(name, "poodle") || name_equals(name, "sslv3")) {
        unsigned i;
        void *px;
        
        /* Change the hello message to including negotiating the use of 
         * the "heartbeat" extension */
        px = ssl_hello(ssl_hello_sslv3_template);
        banner_ssl.hello = ssl_add_cipherspec(px, 0x5600, 1);
        banner_ssl.hello_length = ssl_hello_size(banner_ssl.hello);
        tcpcon->banner1->is_poodle_sslv3 = 1;

        for (i=0; i<65535; i++) {
            banner1->payloads.tcp[i] = &banner_ssl;
        }
        
        return;
    }

    
    /*
     * You can reconfigure the "hello" message to be anything
     * you want.
     */
    if (name_equals(name, "hello-string")) {
        struct ProtocolParserStream *x;
        const char *p = strchr(name, '[');
        unsigned port;


        if (p == NULL) {
            fprintf(stderr, "tcpcon: parmeter: expected array []: %s\n", name);
            exit(1);
        }
        port = (unsigned)strtoul(p+1, 0, 0);

        x = banner1->payloads.tcp[port];
        if (x == NULL) {
            x = CALLOC(1, sizeof(*x));
            x->name = "(allocated)";
        }

        x->hello = MALLOC(value_length);
        x->hello_length = base64_decode((char*)x->hello, value_length, value, value_length);

        banner1->payloads.tcp[port] = x;
    }

}