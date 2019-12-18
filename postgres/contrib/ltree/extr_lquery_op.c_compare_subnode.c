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
struct TYPE_3__ {char* name; int len; } ;
typedef  TYPE_1__ ltree_level ;

/* Variables and functions */
 char* getlexeme (char*,char*,int*) ; 
 int stub1 (char const*,char const*,size_t) ; 

bool
compare_subnode(ltree_level *t, char *qn, int len, int (*cmpptr) (const char *, const char *, size_t), bool anyend)
{
	char	   *endt = t->name + t->len;
	char	   *endq = qn + len;
	char	   *tn;
	int			lent,
				lenq;
	bool		isok;

	while ((qn = getlexeme(qn, endq, &lenq)) != NULL)
	{
		tn = t->name;
		isok = false;
		while ((tn = getlexeme(tn, endt, &lent)) != NULL)
		{
			if (
				(
				 lent == lenq ||
				 (lent > lenq && anyend)
				 ) &&
				(*cmpptr) (qn, tn, lenq) == 0)
			{

				isok = true;
				break;
			}
			tn += lent;
		}

		if (!isok)
			return false;
		qn += lenq;
	}

	return true;
}