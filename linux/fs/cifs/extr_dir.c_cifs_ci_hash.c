#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wchar_t ;
struct qstr {int len; int /*<<< orphan*/  hash; int /*<<< orphan*/ * name; } ;
struct nls_table {int (* char2uni ) (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ;} ;
struct dentry {int /*<<< orphan*/  d_sb; } ;
struct TYPE_2__ {struct nls_table* local_nls; } ;

/* Variables and functions */
 TYPE_1__* CIFS_SB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cifs_toupper (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  end_name_hash (unsigned long) ; 
 unsigned long init_name_hash (struct dentry const*) ; 
 unsigned long partial_name_hash (int /*<<< orphan*/ ,unsigned long) ; 
 int stub1 (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int cifs_ci_hash(const struct dentry *dentry, struct qstr *q)
{
	struct nls_table *codepage = CIFS_SB(dentry->d_sb)->local_nls;
	unsigned long hash;
	wchar_t c;
	int i, charlen;

	hash = init_name_hash(dentry);
	for (i = 0; i < q->len; i += charlen) {
		charlen = codepage->char2uni(&q->name[i], q->len - i, &c);
		/* error out if we can't convert the character */
		if (unlikely(charlen < 0))
			return charlen;
		hash = partial_name_hash(cifs_toupper(c), hash);
	}
	q->hash = end_name_hash(hash);

	return 0;
}