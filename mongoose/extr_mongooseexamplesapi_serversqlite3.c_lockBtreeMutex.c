#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int locked; TYPE_2__* db; TYPE_1__* pBt; } ;
struct TYPE_6__ {int /*<<< orphan*/  mutex; } ;
struct TYPE_5__ {TYPE_2__* db; int /*<<< orphan*/  mutex; } ;
typedef  TYPE_3__ Btree ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  sqlite3_mutex_enter (int /*<<< orphan*/ ) ; 
 int sqlite3_mutex_held (int /*<<< orphan*/ ) ; 
 int sqlite3_mutex_notheld (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void lockBtreeMutex(Btree *p){
  assert( p->locked==0 );
  assert( sqlite3_mutex_notheld(p->pBt->mutex) );
  assert( sqlite3_mutex_held(p->db->mutex) );

  sqlite3_mutex_enter(p->pBt->mutex);
  p->pBt->db = p->db;
  p->locked = 1;
}