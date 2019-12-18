#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ tb_buf; scalar_t__ tb_noremap; } ;

/* Variables and functions */
 int /*<<< orphan*/  EMSG2 (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  _ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  e_intern2 ; 
 scalar_t__ noremapbuf_init ; 
 TYPE_1__ typebuf ; 
 scalar_t__ typebuf_init ; 
 int /*<<< orphan*/  vim_free (scalar_t__) ; 

void
free_typebuf()
{
    if (typebuf.tb_buf == typebuf_init)
	EMSG2(_(e_intern2), "Free typebuf 1");
    else
	vim_free(typebuf.tb_buf);
    if (typebuf.tb_noremap == noremapbuf_init)
	EMSG2(_(e_intern2), "Free typebuf 2");
    else
	vim_free(typebuf.tb_noremap);
}