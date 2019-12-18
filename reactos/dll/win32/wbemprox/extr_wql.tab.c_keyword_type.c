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
struct keyword {unsigned int len; int type; int /*<<< orphan*/  const* name; } ;
typedef  int /*<<< orphan*/  WCHAR ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 unsigned int MAX_TOKEN_LEN ; 
 int TK_ID ; 
 struct keyword* bsearch (struct keyword*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmp_keyword ; 
 int /*<<< orphan*/  keyword_table ; 

__attribute__((used)) static int keyword_type( const WCHAR *str, unsigned int len )
{
    struct keyword key, *ret;

    if (len > MAX_TOKEN_LEN) return TK_ID;

    key.name = str;
    key.len  = len;
    key.type = 0;
    ret = bsearch( &key, keyword_table, ARRAY_SIZE(keyword_table), sizeof(struct keyword), cmp_keyword );
    if (ret) return ret->type;
    return TK_ID;
}