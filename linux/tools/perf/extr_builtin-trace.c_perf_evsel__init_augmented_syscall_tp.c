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
struct tep_format_field {int /*<<< orphan*/  offset; int /*<<< orphan*/  size; } ;
struct syscall_tp {int /*<<< orphan*/  id; } ;
struct evsel {struct syscall_tp* priv; int /*<<< orphan*/  needs_swap; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 scalar_t__ __tp_field__init_uint (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct syscall_tp* malloc (int) ; 
 struct tep_format_field* perf_evsel__field (struct evsel*,char*) ; 
 int /*<<< orphan*/  zfree (struct syscall_tp**) ; 

__attribute__((used)) static int perf_evsel__init_augmented_syscall_tp(struct evsel *evsel, struct evsel *tp)
{
	struct syscall_tp *sc = evsel->priv = malloc(sizeof(struct syscall_tp));

	if (evsel->priv != NULL) {
		struct tep_format_field *syscall_id = perf_evsel__field(tp, "id");
		if (syscall_id == NULL)
			syscall_id = perf_evsel__field(tp, "__syscall_nr");
		if (syscall_id == NULL)
			goto out_delete;
		if (__tp_field__init_uint(&sc->id, syscall_id->size, syscall_id->offset, evsel->needs_swap))
			goto out_delete;

		return 0;
	}

	return -ENOMEM;
out_delete:
	zfree(&evsel->priv);
	return -EINVAL;
}