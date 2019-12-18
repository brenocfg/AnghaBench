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
typedef  scalar_t__ uint8_t ;
struct gc_arena {int dummy; } ;

/* Variables and functions */
 scalar_t__ gc_malloc (int,int,struct gc_arena*) ; 
 int /*<<< orphan*/  msg (int,char*,...) ; 
 int sscanf (char*,char*,int*) ; 
 int strlen (char const*) ; 

__attribute__((used)) static uint8_t *
parse_hash_fingerprint(const char *str, int nbytes, int msglevel, struct gc_arena *gc)
{
    int i;
    const char *cp = str;
    uint8_t *ret = (uint8_t *) gc_malloc(nbytes, true, gc);
    char term = 1;
    int byte;
    char bs[3];

    for (i = 0; i < nbytes; ++i)
    {
        if (strlen(cp) < 2)
        {
            msg(msglevel, "format error in hash fingerprint: %s", str);
        }
        bs[0] = *cp++;
        bs[1] = *cp++;
        bs[2] = 0;
        byte = 0;
        if (sscanf(bs, "%x", &byte) != 1)
        {
            msg(msglevel, "format error in hash fingerprint hex byte: %s", str);
        }
        ret[i] = (uint8_t)byte;
        term = *cp++;
        if (term != ':' && term != 0)
        {
            msg(msglevel, "format error in hash fingerprint delimiter: %s", str);
        }
        if (term == 0)
        {
            break;
        }
    }
    if (term != 0 || i != nbytes-1)
    {
        msg(msglevel, "hash fingerprint is different length than expected (%d bytes): %s", nbytes, str);
    }
    return ret;
}