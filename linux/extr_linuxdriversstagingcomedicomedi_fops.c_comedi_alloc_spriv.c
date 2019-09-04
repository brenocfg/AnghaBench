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
struct comedi_subdevice {void* private; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  comedi_set_spriv_auto_free (struct comedi_subdevice*) ; 
 void* kzalloc (size_t,int /*<<< orphan*/ ) ; 

void *comedi_alloc_spriv(struct comedi_subdevice *s, size_t size)
{
	s->private = kzalloc(size, GFP_KERNEL);
	if (s->private)
		comedi_set_spriv_auto_free(s);
	return s->private;
}