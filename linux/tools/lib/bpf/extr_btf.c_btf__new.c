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
struct btf {int fd; int /*<<< orphan*/  data_size; int /*<<< orphan*/  data; } ;
typedef  int /*<<< orphan*/  __u8 ;
typedef  int /*<<< orphan*/  __u32 ;

/* Variables and functions */
 int ENOMEM ; 
 struct btf* ERR_PTR (int) ; 
 int /*<<< orphan*/  btf__free (struct btf*) ; 
 int btf_parse_hdr (struct btf*) ; 
 int btf_parse_str_sec (struct btf*) ; 
 int btf_parse_type_sec (struct btf*) ; 
 struct btf* calloc (int,int) ; 
 int /*<<< orphan*/  malloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

struct btf *btf__new(__u8 *data, __u32 size)
{
	struct btf *btf;
	int err;

	btf = calloc(1, sizeof(struct btf));
	if (!btf)
		return ERR_PTR(-ENOMEM);

	btf->fd = -1;

	btf->data = malloc(size);
	if (!btf->data) {
		err = -ENOMEM;
		goto done;
	}

	memcpy(btf->data, data, size);
	btf->data_size = size;

	err = btf_parse_hdr(btf);
	if (err)
		goto done;

	err = btf_parse_str_sec(btf);
	if (err)
		goto done;

	err = btf_parse_type_sec(btf);

done:
	if (err) {
		btf__free(btf);
		return ERR_PTR(err);
	}

	return btf;
}