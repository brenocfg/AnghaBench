#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  hash_ctl ;
struct TYPE_10__ {int keysize; int entrysize; int /*<<< orphan*/  hcxt; } ;
struct TYPE_9__ {int /*<<< orphan*/  context; } ;
struct TYPE_8__ {int /*<<< orphan*/ * toast_hash; } ;
typedef  int /*<<< orphan*/  ReorderBufferToastEnt ;
typedef  TYPE_1__ ReorderBufferTXN ;
typedef  TYPE_2__ ReorderBuffer ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_3__ HASHCTL ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int HASH_BLOBS ; 
 int HASH_CONTEXT ; 
 int HASH_ELEM ; 
 int /*<<< orphan*/ * hash_create (char*,int,TYPE_3__*,int) ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
ReorderBufferToastInitHash(ReorderBuffer *rb, ReorderBufferTXN *txn)
{
	HASHCTL		hash_ctl;

	Assert(txn->toast_hash == NULL);

	memset(&hash_ctl, 0, sizeof(hash_ctl));
	hash_ctl.keysize = sizeof(Oid);
	hash_ctl.entrysize = sizeof(ReorderBufferToastEnt);
	hash_ctl.hcxt = rb->context;
	txn->toast_hash = hash_create("ReorderBufferToastHash", 5, &hash_ctl,
								  HASH_ELEM | HASH_BLOBS | HASH_CONTEXT);
}