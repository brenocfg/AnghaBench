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

/* Variables and functions */
 char** sqlite3CompileOptions (int*) ; 

const char *sqlite3_compileoption_get(int N){
  int nOpt;
  const char **azCompileOpt;
  azCompileOpt = sqlite3CompileOptions(&nOpt);
  if( N>=0 && N<nOpt ){
    return azCompileOpt[N];
  }
  return 0;
}