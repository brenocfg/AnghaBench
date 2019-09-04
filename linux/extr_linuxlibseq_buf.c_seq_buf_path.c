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
struct seq_buf {int /*<<< orphan*/  size; } ;
struct path {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (char*) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 char* d_path (struct path const*,char*,size_t) ; 
 char* mangle_path (char*,char*,char const*) ; 
 int /*<<< orphan*/  seq_buf_commit (struct seq_buf*,int) ; 
 size_t seq_buf_get_buf (struct seq_buf*,char**) ; 

int seq_buf_path(struct seq_buf *s, const struct path *path, const char *esc)
{
	char *buf;
	size_t size = seq_buf_get_buf(s, &buf);
	int res = -1;

	WARN_ON(s->size == 0);

	if (size) {
		char *p = d_path(path, buf, size);
		if (!IS_ERR(p)) {
			char *end = mangle_path(buf, p, esc);
			if (end)
				res = end - buf;
		}
	}
	seq_buf_commit(s, res);

	return res;
}