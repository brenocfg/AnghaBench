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
struct Banner1 {scalar_t__ http_fields; scalar_t__ smack; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct Banner1*) ; 
 int /*<<< orphan*/  smack_destroy (scalar_t__) ; 

void
banner1_destroy(struct Banner1 *b)
{
    if (b == NULL)
        return;
    if (b->smack)
        smack_destroy(b->smack);
    if (b->http_fields)
        smack_destroy(b->http_fields);
    free(b);
}