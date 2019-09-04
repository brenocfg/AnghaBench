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
typedef  int /*<<< orphan*/  va_list ;
struct bpf_verifier_log {char* kbuf; int len_total; int len_used; int /*<<< orphan*/ * ubuf; } ;

/* Variables and functions */
 int BPF_VERIFIER_TMP_LOG_SIZE ; 
 int /*<<< orphan*/  WARN_ONCE (int,char*) ; 
 int /*<<< orphan*/  copy_to_user (int /*<<< orphan*/ *,char*,unsigned int) ; 
 unsigned int min (int,unsigned int) ; 
 unsigned int vscnprintf (char*,int,char const*,int /*<<< orphan*/ ) ; 

void bpf_verifier_vlog(struct bpf_verifier_log *log, const char *fmt,
		       va_list args)
{
	unsigned int n;

	n = vscnprintf(log->kbuf, BPF_VERIFIER_TMP_LOG_SIZE, fmt, args);

	WARN_ONCE(n >= BPF_VERIFIER_TMP_LOG_SIZE - 1,
		  "verifier log line truncated - local buffer too short\n");

	n = min(log->len_total - log->len_used - 1, n);
	log->kbuf[n] = '\0';

	if (!copy_to_user(log->ubuf + log->len_used, log->kbuf, n + 1))
		log->len_used += n;
	else
		log->ubuf = NULL;
}