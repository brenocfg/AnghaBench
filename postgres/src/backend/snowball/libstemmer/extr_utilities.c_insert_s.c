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
typedef  int /*<<< orphan*/  symbol ;
struct SN_env {int bra; int ket; } ;

/* Variables and functions */
 scalar_t__ replace_s (struct SN_env*,int,int,int,int /*<<< orphan*/  const*,int*) ; 

extern int insert_s(struct SN_env * z, int bra, int ket, int s_size, const symbol * s) {
    int adjustment;
    if (replace_s(z, bra, ket, s_size, s, &adjustment))
        return -1;
    if (bra <= z->bra) z->bra += adjustment;
    if (bra <= z->ket) z->ket += adjustment;
    return 0;
}