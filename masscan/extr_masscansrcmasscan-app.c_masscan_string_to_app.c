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
typedef  enum ApplicationProtocol { ____Placeholder_ApplicationProtocol } ApplicationProtocol ;

/* Variables and functions */
#define  PROTO_COAP 152 
#define  PROTO_DNS_VERSIONBIND 151 
#define  PROTO_FTP 150 
#define  PROTO_HEARTBLEED 149 
#define  PROTO_HTML_FULL 148 
#define  PROTO_HTML_TITLE 147 
#define  PROTO_HTTP 146 
#define  PROTO_IMAP4 145 
#define  PROTO_MEMCACHED 144 
#define  PROTO_NBTSTAT 143 
#define  PROTO_NTP 142 
#define  PROTO_POP3 141 
#define  PROTO_SAFE 140 
#define  PROTO_SCRIPTING 139 
#define  PROTO_SMB 138 
#define  PROTO_SNMP 137 
#define  PROTO_SSH1 136 
#define  PROTO_SSH2 135 
#define  PROTO_SSL3 134 
#define  PROTO_TICKETBLEED 133 
#define  PROTO_UDP_ZEROACCESS 132 
#define  PROTO_VERSIONING 131 
#define  PROTO_VNC_RFB 130 
#define  PROTO_VULN 129 
#define  PROTO_X509_CERT 128 
 scalar_t__ strcmp (char const*,char const*) ; 

enum ApplicationProtocol
masscan_string_to_app(const char *str)
{
    const static struct {
        const char *name;
        enum ApplicationProtocol value;
    } list[] = {
        {"ssh1",    PROTO_SSH1},
        {"ssh2",    PROTO_SSH2},
        {"ssh",     PROTO_SSH2},
        {"http",    PROTO_HTTP},
        {"ftp",     PROTO_FTP},
        {"dns-ver", PROTO_DNS_VERSIONBIND},
        {"snmp",    PROTO_SNMP},
        {"ssh2",    PROTO_SSH2},
        {"nbtstat", PROTO_NBTSTAT},
        {"ssl",     PROTO_SSL3},
        {"smb",     PROTO_SMB},
        {"pop",     PROTO_POP3},
        {"imap",    PROTO_IMAP4},
        {"x509",    PROTO_X509_CERT},
        {"zeroaccess",  PROTO_UDP_ZEROACCESS},
        {"title",       PROTO_HTML_TITLE},
        {"html",        PROTO_HTML_FULL},
        {"ntp",         PROTO_NTP},
        {"vuln",        PROTO_VULN},
        {"heartbleed",  PROTO_HEARTBLEED},
        {"ticketbleed", PROTO_TICKETBLEED},
        {"vnc",         PROTO_VNC_RFB},
        {"safe",        PROTO_SAFE},
        {"memcached",   PROTO_MEMCACHED},
        {"scripting",   PROTO_SCRIPTING},
        {"versioning",  PROTO_VERSIONING},
        {"coap",        PROTO_COAP},
        {0,0}
    };
    size_t i;
    
    for (i=0; list[i].name; i++) {
        if (strcmp(str, list[i].name) == 0)
            return list[i].value;
    }
    return 0;
}