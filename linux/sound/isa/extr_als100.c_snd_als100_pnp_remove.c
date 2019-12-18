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
struct pnp_card_link {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  pnp_get_card_drvdata (struct pnp_card_link*) ; 
 int /*<<< orphan*/  pnp_set_card_drvdata (struct pnp_card_link*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_card_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void snd_als100_pnp_remove(struct pnp_card_link *pcard)
{
	snd_card_free(pnp_get_card_drvdata(pcard));
	pnp_set_card_drvdata(pcard, NULL);
}