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
typedef  int /*<<< orphan*/  tmp ;
typedef  enum ApplicationProtocol { ____Placeholder_ApplicationProtocol } ApplicationProtocol ;

/* Variables and functions */
#define  PROTO_COAP 155 
#define  PROTO_DNS_VERSIONBIND 154 
#define  PROTO_FTP 153 
#define  PROTO_HEARTBLEED 152 
#define  PROTO_HEUR 151 
#define  PROTO_HTML_FULL 150 
#define  PROTO_HTML_TITLE 149 
#define  PROTO_HTTP 148 
#define  PROTO_IMAP4 147 
#define  PROTO_MEMCACHED 146 
#define  PROTO_NBTSTAT 145 
#define  PROTO_NONE 144 
#define  PROTO_NTP 143 
#define  PROTO_POP3 142 
#define  PROTO_SAFE 141 
#define  PROTO_SCRIPTING 140 
#define  PROTO_SMB 139 
#define  PROTO_SMTP 138 
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
 int /*<<< orphan*/  sprintf_s (char*,int,char*,int) ; 

const char *
masscan_app_to_string(enum ApplicationProtocol proto)
{
    static char tmp[64];

    switch (proto) {
    case PROTO_NONE: return "unknown";
    case PROTO_HEUR: return "unknown";
    case PROTO_SSH1: return "ssh";
    case PROTO_SSH2: return "ssh";
    case PROTO_HTTP: return "http";
    case PROTO_FTP: return "ftp";
    case PROTO_DNS_VERSIONBIND: return "dns-ver";
    case PROTO_SNMP: return "snmp";
    case PROTO_NBTSTAT: return "nbtstat";
    case PROTO_SSL3:    return "ssl";
    case PROTO_SMB:     return "smb";
    case PROTO_SMTP:    return "smtp";
    case PROTO_POP3:    return "pop";
    case PROTO_IMAP4:   return "imap";
    case PROTO_UDP_ZEROACCESS: return "zeroaccess";
    case PROTO_X509_CERT: return "X509";
    case PROTO_HTML_TITLE: return "title";
    case PROTO_HTML_FULL: return "html";
    case PROTO_NTP:     return "ntp";
    case PROTO_VULN:    return "vuln";
    case PROTO_HEARTBLEED:    return "heartbleed";
    case PROTO_TICKETBLEED:    return "ticketbleed";
    case PROTO_VNC_RFB: return "vnc";
    case PROTO_SAFE:    return "safe";
    case PROTO_MEMCACHED: return "memcached";
    case PROTO_SCRIPTING:      return "scripting";
    case PROTO_VERSIONING:     return "versioning";
    case PROTO_COAP:           return "coap";
            
    default:
        sprintf_s(tmp, sizeof(tmp), "(%u)", proto);
        return tmp;
    }
}