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
struct SN_env {int l; int c; int /*<<< orphan*/  const* p; } ;

/* Variables and functions */
 int CAPACITY (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  SET_SIZE (int /*<<< orphan*/  const*,int) ; 
 int SIZE (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  const* create_s () ; 
 int /*<<< orphan*/  const* increase_size (int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  memmove (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int) ; 

extern int replace_s(struct SN_env * z, int c_bra, int c_ket, int s_size, const symbol * s, int * adjptr)
{
    int adjustment;
    int len;
    if (z->p == NULL) {
        z->p = create_s();
        if (z->p == NULL) return -1;
    }
    adjustment = s_size - (c_ket - c_bra);
    len = SIZE(z->p);
    if (adjustment != 0) {
        if (adjustment + len > CAPACITY(z->p)) {
            z->p = increase_size(z->p, adjustment + len);
            if (z->p == NULL) return -1;
        }
        memmove(z->p + c_ket + adjustment,
                z->p + c_ket,
                (len - c_ket) * sizeof(symbol));
        SET_SIZE(z->p, adjustment + len);
        z->l += adjustment;
        if (z->c >= c_ket)
            z->c += adjustment;
        else if (z->c > c_bra)
            z->c = c_bra;
    }
    if (s_size) memmove(z->p + c_bra, s, s_size * sizeof(symbol));
    if (adjptr != NULL)
        *adjptr = adjustment;
    return 0;
}