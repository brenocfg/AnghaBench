#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ buf; } ;
struct TYPE_5__ {scalar_t__ hashso_bucket_buf; scalar_t__ hashso_split_bucket_buf; int hashso_buc_populated; int hashso_buc_split; TYPE_1__ currPos; } ;
typedef  int /*<<< orphan*/  Relation ;
typedef  TYPE_2__* HashScanOpaque ;

/* Variables and functions */
 scalar_t__ BufferIsValid (scalar_t__) ; 
 void* InvalidBuffer ; 
 int /*<<< orphan*/  _hash_dropbuf (int /*<<< orphan*/ ,scalar_t__) ; 

void
_hash_dropscanbuf(Relation rel, HashScanOpaque so)
{
	/* release pin we hold on primary bucket page */
	if (BufferIsValid(so->hashso_bucket_buf) &&
		so->hashso_bucket_buf != so->currPos.buf)
		_hash_dropbuf(rel, so->hashso_bucket_buf);
	so->hashso_bucket_buf = InvalidBuffer;

	/* release pin we hold on primary bucket page  of bucket being split */
	if (BufferIsValid(so->hashso_split_bucket_buf) &&
		so->hashso_split_bucket_buf != so->currPos.buf)
		_hash_dropbuf(rel, so->hashso_split_bucket_buf);
	so->hashso_split_bucket_buf = InvalidBuffer;

	/* release any pin we still hold */
	if (BufferIsValid(so->currPos.buf))
		_hash_dropbuf(rel, so->currPos.buf);
	so->currPos.buf = InvalidBuffer;

	/* reset split scan */
	so->hashso_buc_populated = false;
	so->hashso_buc_split = false;
}