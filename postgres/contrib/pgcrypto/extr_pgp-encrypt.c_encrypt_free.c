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
struct EncStat {scalar_t__ ciph; } ;

/* Variables and functions */
 int /*<<< orphan*/  pgp_cfb_free (scalar_t__) ; 
 int /*<<< orphan*/  px_free (struct EncStat*) ; 
 int /*<<< orphan*/  px_memset (struct EncStat*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
encrypt_free(void *priv)
{
	struct EncStat *st = priv;

	if (st->ciph)
		pgp_cfb_free(st->ciph);
	px_memset(st, 0, sizeof(*st));
	px_free(st);
}