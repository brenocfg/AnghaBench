#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ pos; scalar_t__ fileLen; int /*<<< orphan*/  AH; } ;
typedef  TYPE_1__ TAR_MEMBER ;

/* Variables and functions */
 size_t _tarReadRaw (int /*<<< orphan*/ ,void*,size_t,TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static size_t
tarRead(void *buf, size_t len, TAR_MEMBER *th)
{
	size_t		res;

	if (th->pos + len > th->fileLen)
		len = th->fileLen - th->pos;

	if (len <= 0)
		return 0;

	res = _tarReadRaw(th->AH, buf, len, th, NULL);

	th->pos += res;

	return res;
}