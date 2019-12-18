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
struct TYPE_4__ {int /*<<< orphan*/  zToken; } ;
struct TYPE_5__ {scalar_t__ op; TYPE_1__ u; } ;
typedef  TYPE_2__ Expr ;

/* Variables and functions */
 int /*<<< orphan*/  SQLITE_UTF8 ; 
 scalar_t__ TK_FLOAT ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  sqlite3AtoF (int /*<<< orphan*/ ,double*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3Strlen30 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int exprProbability(Expr *p){
  double r = -1.0;
  if( p->op!=TK_FLOAT ) return -1;
  sqlite3AtoF(p->u.zToken, &r, sqlite3Strlen30(p->u.zToken), SQLITE_UTF8);
  assert( r>=0.0 );
  if( r>1.0 ) return -1;
  return (int)(r*134217728.0);
}