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
typedef  int /*<<< orphan*/  StrAccum ;
typedef  int /*<<< orphan*/  Index ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  explainIndexColumnName (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sqlite3StrAccumAppend (int /*<<< orphan*/ *,char const*,int) ; 
 int /*<<< orphan*/  sqlite3StrAccumAppendAll (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void explainAppendTerm(
  StrAccum *pStr,             /* The text expression being built */
  Index *pIdx,                /* Index to read column names from */
  int nTerm,                  /* Number of terms */
  int iTerm,                  /* Zero-based index of first term. */
  int bAnd,                   /* Non-zero to append " AND " */
  const char *zOp             /* Name of the operator */
){
  int i;

  assert( nTerm>=1 );
  if( bAnd ) sqlite3StrAccumAppend(pStr, " AND ", 5);

  if( nTerm>1 ) sqlite3StrAccumAppend(pStr, "(", 1);
  for(i=0; i<nTerm; i++){
    if( i ) sqlite3StrAccumAppend(pStr, ",", 1);
    sqlite3StrAccumAppendAll(pStr, explainIndexColumnName(pIdx, iTerm+i));
  }
  if( nTerm>1 ) sqlite3StrAccumAppend(pStr, ")", 1);

  sqlite3StrAccumAppend(pStr, zOp, 1);

  if( nTerm>1 ) sqlite3StrAccumAppend(pStr, "(", 1);
  for(i=0; i<nTerm; i++){
    if( i ) sqlite3StrAccumAppend(pStr, ",", 1);
    sqlite3StrAccumAppend(pStr, "?", 1);
  }
  if( nTerm>1 ) sqlite3StrAccumAppend(pStr, ")", 1);
}