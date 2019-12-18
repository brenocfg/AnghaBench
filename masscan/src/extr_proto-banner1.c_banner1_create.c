#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_34__   TYPE_9__ ;
typedef  struct TYPE_33__   TYPE_8__ ;
typedef  struct TYPE_32__   TYPE_7__ ;
typedef  struct TYPE_31__   TYPE_6__ ;
typedef  struct TYPE_30__   TYPE_5__ ;
typedef  struct TYPE_29__   TYPE_4__ ;
typedef  struct TYPE_28__   TYPE_3__ ;
typedef  struct TYPE_27__   TYPE_2__ ;
typedef  struct TYPE_26__   TYPE_1__ ;
typedef  struct TYPE_25__   TYPE_17__ ;
typedef  struct TYPE_24__   TYPE_16__ ;
typedef  struct TYPE_23__   TYPE_15__ ;
typedef  struct TYPE_22__   TYPE_14__ ;
typedef  struct TYPE_21__   TYPE_13__ ;
typedef  struct TYPE_20__   TYPE_12__ ;
typedef  struct TYPE_19__   TYPE_11__ ;
typedef  struct TYPE_18__   TYPE_10__ ;

/* Type definitions */
struct TYPE_26__ {TYPE_16__** tcp; } ;
struct Banner1 {TYPE_1__ payloads; int /*<<< orphan*/  smack; } ;
struct TYPE_34__ {int /*<<< orphan*/  (* init ) (struct Banner1*) ;} ;
struct TYPE_33__ {int /*<<< orphan*/  (* init ) (struct Banner1*) ;} ;
struct TYPE_32__ {int /*<<< orphan*/  (* init ) (struct Banner1*) ;} ;
struct TYPE_31__ {int /*<<< orphan*/  (* init ) (struct Banner1*) ;} ;
struct TYPE_30__ {int /*<<< orphan*/  (* init ) (struct Banner1*) ;} ;
struct TYPE_29__ {int /*<<< orphan*/  (* init ) (struct Banner1*) ;} ;
struct TYPE_28__ {int /*<<< orphan*/  (* init ) (struct Banner1*) ;} ;
struct TYPE_27__ {int /*<<< orphan*/  is_anchored; int /*<<< orphan*/  pattern_length; scalar_t__ pattern; } ;
struct TYPE_25__ {int /*<<< orphan*/  (* init ) (struct Banner1*) ;} ;
struct TYPE_24__ {int /*<<< orphan*/  (* init ) (struct Banner1*) ;} ;
struct TYPE_23__ {int /*<<< orphan*/  (* init ) (struct Banner1*) ;} ;
struct TYPE_22__ {int /*<<< orphan*/  (* init ) (struct Banner1*) ;} ;
struct TYPE_21__ {int /*<<< orphan*/  (* init ) (struct Banner1*) ;} ;
struct TYPE_20__ {int /*<<< orphan*/  (* init ) (struct Banner1*) ;} ;
struct TYPE_19__ {int /*<<< orphan*/  (* init ) (struct Banner1*) ;} ;
struct TYPE_18__ {int /*<<< orphan*/  (* init ) (struct Banner1*) ;} ;

/* Variables and functions */
 struct Banner1* CALLOC (int,int) ; 
 int /*<<< orphan*/  SMACK_CASE_INSENSITIVE ; 
 TYPE_17__ banner_ftp ; 
 TYPE_16__ banner_http ; 
 TYPE_15__ banner_imap4 ; 
 TYPE_14__ banner_memcached ; 
 TYPE_13__ banner_pop3 ; 
 TYPE_12__ banner_rdp ; 
 TYPE_11__ banner_scripting ; 
 TYPE_10__ banner_smb0 ; 
 TYPE_9__ banner_smb1 ; 
 TYPE_8__ banner_smtp ; 
 TYPE_7__ banner_ssh ; 
 TYPE_6__ banner_ssl ; 
 TYPE_5__ banner_telnet ; 
 TYPE_4__ banner_versioning ; 
 TYPE_3__ banner_vnc ; 
 TYPE_2__* patterns ; 
 int /*<<< orphan*/  smack_add_pattern (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smack_compile (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smack_create (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct Banner1*) ; 
 int /*<<< orphan*/  stub10 (struct Banner1*) ; 
 int /*<<< orphan*/  stub11 (struct Banner1*) ; 
 int /*<<< orphan*/  stub12 (struct Banner1*) ; 
 int /*<<< orphan*/  stub13 (struct Banner1*) ; 
 int /*<<< orphan*/  stub14 (struct Banner1*) ; 
 int /*<<< orphan*/  stub15 (struct Banner1*) ; 
 int /*<<< orphan*/  stub2 (struct Banner1*) ; 
 int /*<<< orphan*/  stub3 (struct Banner1*) ; 
 int /*<<< orphan*/  stub4 (struct Banner1*) ; 
 int /*<<< orphan*/  stub5 (struct Banner1*) ; 
 int /*<<< orphan*/  stub6 (struct Banner1*) ; 
 int /*<<< orphan*/  stub7 (struct Banner1*) ; 
 int /*<<< orphan*/  stub8 (struct Banner1*) ; 
 int /*<<< orphan*/  stub9 (struct Banner1*) ; 

struct Banner1 *
banner1_create(void)
{
    struct Banner1 *b;
    unsigned i;

    b = CALLOC(1, sizeof(*b));
    

    /*
     * This creates a pattern-matching blob for heuristically determining
     * a protocol that runs on wrong ports, such as how FTP servers
     * often respond with "220 " or VNC servers respond with "RFB".
     */
    b->smack = smack_create("banner1", SMACK_CASE_INSENSITIVE);
    for (i=0; patterns[i].pattern; i++)
        smack_add_pattern(
                    b->smack,
                    patterns[i].pattern,
                    patterns[i].pattern_length,
                    i,
                    patterns[i].is_anchored);
    smack_compile(b->smack);

    /*
     * [TODO] These need to be moved into the 'init' functions
     */
    b->payloads.tcp[80] = &banner_http;
    b->payloads.tcp[8080] = &banner_http;
    b->payloads.tcp[139] = (void*)&banner_smb0;
    b->payloads.tcp[445] = (void*)&banner_smb1;
    b->payloads.tcp[443] = (void*)&banner_ssl;   /* HTTP/s */
    b->payloads.tcp[465] = (void*)&banner_ssl;   /* SMTP/s */
    b->payloads.tcp[990] = (void*)&banner_ssl;   /* FTP/s */
    b->payloads.tcp[991] = (void*)&banner_ssl;
    b->payloads.tcp[992] = (void*)&banner_ssl;   /* Telnet/s */
    b->payloads.tcp[993] = (void*)&banner_ssl;   /* IMAP4/s */
    b->payloads.tcp[994] = (void*)&banner_ssl;
    b->payloads.tcp[995] = (void*)&banner_ssl;   /* POP3/s */
    b->payloads.tcp[2083] = (void*)&banner_ssl;  /* cPanel - SSL */
    b->payloads.tcp[2087] = (void*)&banner_ssl;  /* WHM - SSL */
    b->payloads.tcp[2096] = (void*)&banner_ssl;  /* cPanel webmail - SSL */
    b->payloads.tcp[8443] = (void*)&banner_ssl;  /* Plesk Control Panel - SSL */
    b->payloads.tcp[9050] = (void*)&banner_ssl;  /* Tor */
    b->payloads.tcp[8140] = (void*)&banner_ssl;  /* puppet */
    b->payloads.tcp[11211] = (void*)&banner_memcached;
    b->payloads.tcp[23] = (void*)&banner_telnet;
    b->payloads.tcp[3389] = (void*)&banner_rdp;
    
    /* 
     * This goes down the list of all the TCP protocol handlers and initializes
     * them.
     */
    banner_ftp.init(b);
    banner_http.init(b);
    banner_imap4.init(b);
    banner_memcached.init(b);
    banner_pop3.init(b);
    banner_smtp.init(b);
    banner_ssh.init(b);
    banner_ssl.init(b);
    banner_smb0.init(b);
    banner_smb1.init(b);
    banner_telnet.init(b);
    banner_rdp.init(b);
    banner_vnc.init(b);
    
    /* scripting/versioning come after the rest */
    banner_scripting.init(b);
    banner_versioning.init(b);


    return b;
}