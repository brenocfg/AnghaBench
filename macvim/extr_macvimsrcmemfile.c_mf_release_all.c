#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {scalar_t__ mf_fd; TYPE_4__* mf_used_last; } ;
typedef  TYPE_2__ memfile_T ;
struct TYPE_14__ {TYPE_2__* ml_mfp; } ;
struct TYPE_16__ {scalar_t__ b_may_swap; TYPE_1__ b_ml; struct TYPE_16__* b_next; } ;
typedef  TYPE_3__ buf_T ;
struct TYPE_17__ {int bh_flags; struct TYPE_17__* bh_prev; } ;
typedef  TYPE_4__ bhdr_T ;

/* Variables and functions */
 int BH_DIRTY ; 
 int BH_LOCKED ; 
 scalar_t__ FAIL ; 
 int FALSE ; 
 int TRUE ; 
 TYPE_3__* firstbuf ; 
 int /*<<< orphan*/  mf_free_bhdr (TYPE_4__*) ; 
 int /*<<< orphan*/  mf_rem_hash (TYPE_2__*,TYPE_4__*) ; 
 int /*<<< orphan*/  mf_rem_used (TYPE_2__*,TYPE_4__*) ; 
 scalar_t__ mf_write (TYPE_2__*,TYPE_4__*) ; 
 int /*<<< orphan*/  ml_open_file (TYPE_3__*) ; 

int
mf_release_all()
{
    buf_T	*buf;
    memfile_T	*mfp;
    bhdr_T	*hp;
    int		retval = FALSE;

    for (buf = firstbuf; buf != NULL; buf = buf->b_next)
    {
	mfp = buf->b_ml.ml_mfp;
	if (mfp != NULL)
	{
	    /* If no swap file yet, may open one */
	    if (mfp->mf_fd < 0 && buf->b_may_swap)
		ml_open_file(buf);

	    /* only if there is a swapfile */
	    if (mfp->mf_fd >= 0)
	    {
		for (hp = mfp->mf_used_last; hp != NULL; )
		{
		    if (!(hp->bh_flags & BH_LOCKED)
			    && (!(hp->bh_flags & BH_DIRTY)
				|| mf_write(mfp, hp) != FAIL))
		    {
			mf_rem_used(mfp, hp);
			mf_rem_hash(mfp, hp);
			mf_free_bhdr(hp);
			hp = mfp->mf_used_last;	/* re-start, list was changed */
			retval = TRUE;
		    }
		    else
			hp = hp->bh_prev;
		}
	    }
	}
    }
    return retval;
}