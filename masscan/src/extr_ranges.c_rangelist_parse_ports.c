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
struct RangeList {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOG (int /*<<< orphan*/ ,char*,unsigned int,...) ; 
 unsigned int Templ_ICMP_echo ; 
 unsigned int Templ_Oproto_first ; 
 unsigned int Templ_SCTP ; 
 unsigned int Templ_UDP ; 
 scalar_t__ isalpha (char) ; 
 int /*<<< orphan*/  isdigit (char) ; 
 scalar_t__ isspace (char) ; 
 int /*<<< orphan*/  rangelist_add_range (struct RangeList*,unsigned int,unsigned int) ; 
 scalar_t__ strtoul (char*,char**,int /*<<< orphan*/ ) ; 

const char *
rangelist_parse_ports(struct RangeList *ports, const char *string, unsigned *is_error, unsigned proto_offset)
{
    char *p = (char*)string;
    
    *is_error = 0;
    while (*p) {
        unsigned port;
        unsigned end;

        /* skip whitespace */
        while (*p && isspace(*p & 0xFF))
            p++;

        /* end at comment */
        if (*p == 0 || *p == '#')
            break;

        /* special processing. Nmap allows ports to be prefixed with a
         * characters to clarify TCP, UDP, or SCTP */
        if (isalpha(*p&0xFF) && p[1] == ':') {
            switch (*p) {
                case 'T': case 't':
                    proto_offset = 0;
                    break;
                case 'U': case 'u':
                    proto_offset = Templ_UDP;
                    break;
                case 'S': case 's':
                    proto_offset = Templ_SCTP;
                    break;
                case 'O': case 'o':
                    proto_offset = Templ_Oproto_first;
                    break;
                case 'I': case 'i':
                    proto_offset = Templ_ICMP_echo;
                    break;
                default:
                    LOG(0, "bad port charactern = %c\n", p[0]);
                    *is_error = 1;
                    return p;
            }
            p += 2;
        }

        if (!isdigit(p[0] & 0xFF))
            break;

        port = (unsigned)strtoul(p, &p, 0);
        end = port;
        if (*p == '-') {
            p++;
            end = (unsigned)strtoul(p, &p, 0);
        }

        if (port > 0xFF && proto_offset == Templ_Oproto_first) {
            LOG(0, "bad ports: %u-%u\n", port, end);
            *is_error = 2;
            return p;
        } else if (port > 0xFFFF || end > 0xFFFF || end < port) {
            LOG(0, "bad ports: %u-%u\n", port, end);
            *is_error = 2;
            return p;
        } else {
            rangelist_add_range(ports, port+proto_offset, end+proto_offset);
        }
        if (*p == ',')
            p++;
        else
            break;
    }

    return p;
}