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
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_4__ {int tokenType; int len; int /*<<< orphan*/  const* name; } ;
typedef  TYPE_1__ Keyword ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int MAX_TOKEN_LEN ; 
 int TK_ID ; 
 int /*<<< orphan*/  aKeywordTable ; 
 TYPE_1__* bsearch (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  compKeyword ; 

__attribute__((used)) static int sqliteKeywordCode(const WCHAR *z, int n){
  Keyword key, *r;

  if( n>MAX_TOKEN_LEN )
    return TK_ID;

  key.tokenType = 0;
  key.name = z;
  key.len = n;
  r = bsearch( &key, aKeywordTable, ARRAY_SIZE(aKeywordTable), sizeof(Keyword), compKeyword );
  if( r )
    return r->tokenType;
  return TK_ID;
}