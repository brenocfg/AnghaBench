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
struct TYPE_2__ {scalar_t__ expiry_time; int /*<<< orphan*/  flags; } ;
struct ent {TYPE_1__ h; int /*<<< orphan*/  name; int /*<<< orphan*/  id; int /*<<< orphan*/  type; int /*<<< orphan*/  authname; } ;
struct cache_detail {int dummy; } ;
typedef  int /*<<< orphan*/  ent ;

/* Variables and functions */
 int /*<<< orphan*/  CACHE_NEGATIVE ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int IDMAP_NAMESZ ; 
 int /*<<< orphan*/  IDMAP_TYPE_GROUP ; 
 int /*<<< orphan*/  IDMAP_TYPE_USER ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  cache_put (TYPE_1__*,struct cache_detail*) ; 
 scalar_t__ get_expiry (char**) ; 
 struct ent* idtoname_lookup (struct cache_detail*,struct ent*) ; 
 struct ent* idtoname_update (struct cache_detail*,struct ent*,struct ent*) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  memset (struct ent*,int /*<<< orphan*/ ,int) ; 
 int qword_get (char**,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  simple_strtoul (char*,char**,int) ; 
 scalar_t__ strcmp (char*,char*) ; 

__attribute__((used)) static int
idtoname_parse(struct cache_detail *cd, char *buf, int buflen)
{
	struct ent ent, *res;
	char *buf1, *bp;
	int len;
	int error = -EINVAL;

	if (buf[buflen - 1] != '\n')
		return (-EINVAL);
	buf[buflen - 1]= '\0';

	buf1 = kmalloc(PAGE_SIZE, GFP_KERNEL);
	if (buf1 == NULL)
		return (-ENOMEM);

	memset(&ent, 0, sizeof(ent));

	/* Authentication name */
	len = qword_get(&buf, buf1, PAGE_SIZE);
	if (len <= 0 || len >= IDMAP_NAMESZ)
		goto out;
	memcpy(ent.authname, buf1, sizeof(ent.authname));

	/* Type */
	if (qword_get(&buf, buf1, PAGE_SIZE) <= 0)
		goto out;
	ent.type = strcmp(buf1, "user") == 0 ?
		IDMAP_TYPE_USER : IDMAP_TYPE_GROUP;

	/* ID */
	if (qword_get(&buf, buf1, PAGE_SIZE) <= 0)
		goto out;
	ent.id = simple_strtoul(buf1, &bp, 10);
	if (bp == buf1)
		goto out;

	/* expiry */
	ent.h.expiry_time = get_expiry(&buf);
	if (ent.h.expiry_time == 0)
		goto out;

	error = -ENOMEM;
	res = idtoname_lookup(cd, &ent);
	if (!res)
		goto out;

	/* Name */
	error = -EINVAL;
	len = qword_get(&buf, buf1, PAGE_SIZE);
	if (len < 0 || len >= IDMAP_NAMESZ)
		goto out;
	if (len == 0)
		set_bit(CACHE_NEGATIVE, &ent.h.flags);
	else
		memcpy(ent.name, buf1, sizeof(ent.name));
	error = -ENOMEM;
	res = idtoname_update(cd, &ent, res);
	if (res == NULL)
		goto out;

	cache_put(&res->h, cd);
	error = 0;
out:
	kfree(buf1);
	return error;
}