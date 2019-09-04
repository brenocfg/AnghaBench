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
typedef  int /*<<< orphan*/  Vdbe ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 char* sqlite3DbMallocRaw (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sqlite3VdbeDb (int /*<<< orphan*/ *) ; 

__attribute__((used)) static char *dup8bytes(Vdbe *v, const char *in){
  char *out = sqlite3DbMallocRaw(sqlite3VdbeDb(v), 8);
  if( out ){
    memcpy(out, in, 8);
  }
  return out;
}