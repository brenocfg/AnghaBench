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
typedef  int /*<<< orphan*/  bipbuf_t ;

/* Variables and functions */
 int /*<<< orphan*/  bipbuf_init (int /*<<< orphan*/ *,unsigned int const) ; 
 int /*<<< orphan*/  bipbuf_sizeof (unsigned int const) ; 
 int /*<<< orphan*/ * malloc (int /*<<< orphan*/ ) ; 

bipbuf_t *bipbuf_new(const unsigned int size)
{
    bipbuf_t *me = malloc(bipbuf_sizeof(size));
    if (!me)
        return NULL;
    bipbuf_init(me, size);
    return me;
}