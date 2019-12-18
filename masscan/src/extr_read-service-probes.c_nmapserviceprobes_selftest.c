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
struct NmapServiceProbeList {unsigned int line_number; } ;

/* Variables and functions */
 struct NmapServiceProbeList* nmapserviceprobes_new (char*) ; 
 int /*<<< orphan*/  parse_line (struct NmapServiceProbeList*,char const*) ; 

int
nmapserviceprobes_selftest(void)
{
    const char *lines[] = {
        "Exclude 53,T:9100,U:30000-40000\n",
        "Probe UDP DNSStatusRequest q|\\0\\0\\x10\\0\\0\\0\\0\\0\\0\\0\\0\\0|\n",
        "Probe TCP GetRequest q|GET / HTTP/1.0\r\n\r\n|\n",
        "ports 80\n",
        "sslports 443\n",
        "Probe TCP NULL q||\n",
        "ports 21,43,110,113,199,505,540,1248,5432,30444\n",
        "match ftp m/^220.*Welcome to .*Pure-?FTPd (\\d\\S+\\s*)/ p/Pure-FTPd/ v/$1/ cpe:/a:pureftpd:pure-ftpd:$1/\n",
        "match ssh m/^SSH-([\\d.]+)-OpenSSH[_-]([\\w.]+)\\r?\\n/i p/OpenSSH/ v/$2/ i/protocol $1/ cpe:/a:openbsd:openssh:$2/\n",
        "match mysql m|^\\x10\\0\\0\\x01\\xff\\x13\\x04Bad handshake$| p/MySQL/ cpe:/a:mysql:mysql/\n",
        "match chargen m|@ABCDEFGHIJKLMNOPQRSTUVWXYZ|\n",
        "match uucp m|^login: login: login: $| p/NetBSD uucpd/ o/NetBSD/ cpe:/o:netbsd:netbsd/a\n",
        "match printer m|^([\\w-_.]+): lpd: Illegal service request\\n$| p/lpd/ h/$1/\n",
        "match afs m|^[\\d\\D]{28}\\s*(OpenAFS)([\\d\\.]{3}[^\\s\\0]*)\\0| p/$1/ v/$2/\n",
        0
    };
    unsigned i;
    struct NmapServiceProbeList *list = nmapserviceprobes_new("<selftest>");
    
    for (i=0; lines[i]; i++) {
        list->line_number = i;
        parse_line(list, lines[i]);
    }
    
    //nmapserviceprobes_print(list, stdout);
    return 0;
}