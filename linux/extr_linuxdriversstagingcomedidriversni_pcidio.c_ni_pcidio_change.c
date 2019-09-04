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
struct nidio96_private {int /*<<< orphan*/  di_mite_ring; } ;
struct comedi_subdevice {TYPE_1__* async; } ;
struct comedi_device {struct nidio96_private* private; } ;
struct TYPE_2__ {int /*<<< orphan*/  prealloc_bufsz; int /*<<< orphan*/  prealloc_buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int mite_buf_change (int /*<<< orphan*/ ,struct comedi_subdevice*) ; 

__attribute__((used)) static int ni_pcidio_change(struct comedi_device *dev,
			    struct comedi_subdevice *s)
{
	struct nidio96_private *devpriv = dev->private;
	int ret;

	ret = mite_buf_change(devpriv->di_mite_ring, s);
	if (ret < 0)
		return ret;

	memset(s->async->prealloc_buf, 0xaa, s->async->prealloc_bufsz);

	return 0;
}