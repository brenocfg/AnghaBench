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
typedef  int /*<<< orphan*/  rtype ;

/* Variables and functions */

__attribute__((used)) static int _finite(rtype d)
{
#if ENDIAN == ENDIAN_LITTLE
    struct IEEEdp {
    unsigned manl:32;
    unsigned manh:20;
    unsigned exp:11;
    unsigned sign:1;
    } *ip;
#else
    struct IEEEdp {
    unsigned sign:1;
    unsigned exp:11;
    unsigned manh:20;
    unsigned manl:32;
    } *ip;
#endif

    ip = (struct IEEEdp *)&d;
    return (ip->exp != 0x7ff);
}