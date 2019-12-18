#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3_context ;
struct TYPE_3__ {scalar_t__ iJD; int validJD; } ;
typedef  TYPE_1__ DateTime ;

/* Variables and functions */
 scalar_t__ sqlite3StmtCurrentTime (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int setDateTimeToCurrent(sqlite3_context *context, DateTime *p){
  p->iJD = sqlite3StmtCurrentTime(context);
  if( p->iJD>0 ){
    p->validJD = 1;
    return 0;
  }else{
    return 1;
  }
}