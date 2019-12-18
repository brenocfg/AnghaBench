#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned long long uint64_t ;
struct TYPE_7__ {unsigned char* begin; } ;
struct RangeParser {TYPE_1__ ipv6; } ;
struct TYPE_8__ {unsigned long long hi; unsigned long long lo; } ;
typedef  TYPE_2__ ipv6address ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (TYPE_2__*,TYPE_2__*,int) ; 

__attribute__((used)) static void
rangeparse_getipv6(struct RangeParser *p, ipv6address *begin, ipv6address *end)
{
    const unsigned char *address;
    
    address = p->ipv6.begin;
    begin->hi =    (((uint64_t)address[0]) << 56ULL)
    | ((uint64_t)address[1] << 48ULL)
    | ((uint64_t)address[2] << 40ULL)
    | ((uint64_t)address[3] << 32ULL)
    | ((uint64_t)address[4] << 24ULL)
    | ((uint64_t)address[5] << 16ULL)
    | ((uint64_t)address[6] <<  8ULL)
    | ((uint64_t)address[7] <<  0ULL);
    begin->lo =    ((uint64_t)address[ 8] << 56ULL)
    | ((uint64_t)address[ 9] << 48ULL)
    | ((uint64_t)address[10] << 40ULL)
    | ((uint64_t)address[11] << 32ULL)
    | ((uint64_t)address[12] << 24ULL)
    | ((uint64_t)address[13] << 16ULL)
    | ((uint64_t)address[14] <<  8ULL)
    | ((uint64_t)address[15] <<  0ULL);
    
    memcpy(end, begin, sizeof(*begin));
}