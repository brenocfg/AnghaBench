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
typedef  int uint64_t ;
typedef  struct Range {int member_0; unsigned int begin; unsigned int end; int /*<<< orphan*/  member_1; } const Range ;

/* Variables and functions */
 int /*<<< orphan*/  LOG (int /*<<< orphan*/ ,char*,unsigned int,unsigned int,unsigned int,unsigned int,int,int,int,int) ; 
 scalar_t__ isdigit (char const) ; 
 scalar_t__ isspace (char const) ; 
 int parse_ipv4 (char const*,unsigned int*,unsigned int,unsigned int*) ; 
 scalar_t__ strlen (char const*) ; 

struct Range
range_parse_ipv4(const char *line, unsigned *inout_offset, unsigned max)
{
    unsigned offset;
    struct Range result;
    static const struct Range badrange = {0xFFFFFFFF, 0};
    int err;

    if (line == NULL)
        return badrange;

    if (inout_offset == NULL) {
         inout_offset = &offset;
         offset = 0;
         max = (unsigned)strlen(line);
    } else
        offset = *inout_offset;


    /* trim whitespace */
    while (offset < max && isspace(line[offset]&0xFF))
        offset++;

    /* get the first IP address */
    err = parse_ipv4(line, &offset, max, &result.begin);
    if (err) {
        return badrange;
    }
    result.end = result.begin;

    /* trim whitespace */
    while (offset < max && isspace(line[offset]&0xFF))
        offset++;

    /* If onely one IP address, return that */
    if (offset >= max)
        goto end;

    /*
     * Handle CIDR address of the form "10.0.0.0/8"
     */
    if (line[offset] == '/') {
        uint64_t prefix = 0;
        uint64_t mask = 0;
        unsigned digits = 0;

        /* skip slash */
        offset++;

        if (!isdigit(line[offset]&0xFF)) {
            return badrange;
        }

        /* strip leading zeroes */
        while (offset<max && line[offset] == '0')
            offset++;

        /* parse decimal integer */
        while (offset<max && isdigit(line[offset]&0xFF)) {
            prefix = prefix * 10 + (line[offset++] - '0');
            if (++digits > 2)
                return badrange;
        }
        if (prefix > 32)
            return badrange;

        /* Create the mask from the prefix */
        mask = 0xFFFFFFFF00000000ULL >> prefix;

        /* Mask off any non-zero bits from the start
         * TODO print warning */
        result.begin &= mask;

        /* Set all suffix bits to 1, so that 192.168.1.0/24 has
         * an ending address of 192.168.1.255. */
        result.end = result.begin | (unsigned)~mask;
        goto end;
    }

    /*
     * Handle a dashed range like "10.0.0.100-10.0.0.200"
     */
    if (offset<max && line[offset] == '-') {
        unsigned ip;

        offset++;
        err = parse_ipv4(line, &offset, max, &ip);
        if (err)
            return badrange;
        if (ip < result.begin) {
            result.begin = 0xFFFFFFFF;
            result.end = 0x00000000;
            LOG(0, "err: ending addr %u.%u.%u.%u cannot come before starting addr %u.%u.%u.%u\n",
                ((ip>>24)&0xFF), ((ip>>16)&0xFF), ((ip>>8)&0xFF), ((ip>>0)&0xFF),
                ((result.begin>>24)&0xFF), ((result.begin>>16)&0xFF), ((result.begin>>8)&0xFF), ((result.begin>>0)&0xFF)
                );
        } else
            result.end = ip;
        goto end;
    }

end:
    *inout_offset = offset;
    return result;
}