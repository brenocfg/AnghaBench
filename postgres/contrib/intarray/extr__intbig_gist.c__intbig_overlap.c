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
typedef  int /*<<< orphan*/  int32 ;
typedef  int /*<<< orphan*/  GISTTYPE ;
typedef  int /*<<< orphan*/  ArrayType ;

/* Variables and functions */
 int ARRNELEMS (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ARRPTR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CHECKARRVALID (int /*<<< orphan*/ *) ; 
 scalar_t__ GETBIT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GETSIGN (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HASHVAL (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
_intbig_overlap(GISTTYPE *a, ArrayType *b)
{
	int			num = ARRNELEMS(b);
	int32	   *ptr = ARRPTR(b);

	CHECKARRVALID(b);

	while (num--)
	{
		if (GETBIT(GETSIGN(a), HASHVAL(*ptr)))
			return true;
		ptr++;
	}

	return false;
}