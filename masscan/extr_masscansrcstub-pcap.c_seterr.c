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

/* Variables and functions */
 int PCAP_ERRBUF_SIZE ; 
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 
 size_t strlen (char const*) ; 

__attribute__((used)) static void seterr(char *errbuf, const char *msg)
{
    size_t length = strlen(msg);
    
    if (length > PCAP_ERRBUF_SIZE-1)
    length = PCAP_ERRBUF_SIZE-1;
    memcpy(errbuf, msg, length);
    errbuf[length] = '\0';
}