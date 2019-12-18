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
struct lzstate {int getcur; int getlen; int /*<<< orphan*/ * get; int /*<<< orphan*/  realfd; } ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  GETLEN ; 
 int HFILE_ERROR ; 
 int _lread (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
_lzget(struct lzstate *lzs,BYTE *b) {
	if (lzs->getcur<lzs->getlen) {
		*b		= lzs->get[lzs->getcur++];
		return		1;
	} else {
		int ret = _lread(lzs->realfd,lzs->get,GETLEN);
		if (ret==HFILE_ERROR)
			return HFILE_ERROR;
		if (ret==0)
			return 0;
		lzs->getlen	= ret;
		lzs->getcur	= 1;
		*b		= *(lzs->get);
		return 1;
	}
}