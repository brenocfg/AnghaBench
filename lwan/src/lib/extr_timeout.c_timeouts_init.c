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
struct timeouts {scalar_t__ curtime; scalar_t__* pending; scalar_t__ expired; scalar_t__** wheel; } ;

/* Variables and functions */
 unsigned int N_ELEMENTS (scalar_t__*) ; 
 int /*<<< orphan*/  list_head_init (scalar_t__*) ; 

__attribute__((used)) static struct timeouts *timeouts_init(struct timeouts *T)
{
    unsigned i, j;

    for (i = 0; i < N_ELEMENTS(T->wheel); i++) {
        for (j = 0; j < N_ELEMENTS(T->wheel[i]); j++) {
            list_head_init(&T->wheel[i][j]);
        }
    }

    list_head_init(&T->expired);

    for (i = 0; i < N_ELEMENTS(T->pending); i++) {
        T->pending[i] = 0;
    }

    T->curtime = 0;

    return T;
}