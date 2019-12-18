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
struct TYPE_4__ {int nAlloc; char* zText; int /*<<< orphan*/  nChar; } ;
typedef  TYPE_1__ sqlite3_str ;
typedef  int i64 ;

/* Variables and functions */
 int sqlite3StrAccumEnlarge (TYPE_1__*,int) ; 
 int /*<<< orphan*/  testcase (int) ; 

void sqlite3_str_appendchar(sqlite3_str *p, int N, char c){
  testcase( p->nChar + (i64)N > 0x7fffffff );
  if( p->nChar+(i64)N >= p->nAlloc && (N = sqlite3StrAccumEnlarge(p, N))<=0 ){
    return;
  }
  while( (N--)>0 ) p->zText[p->nChar++] = c;
}