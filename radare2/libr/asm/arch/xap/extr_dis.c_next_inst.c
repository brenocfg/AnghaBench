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
struct state {scalar_t__ s_format; } ;
struct directive {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct directive*) ; 
 struct directive* malloc (int) ; 
 int /*<<< orphan*/  memset (struct directive*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int read_bin (struct state*,struct directive*) ; 
 int read_text (struct state*,struct directive*) ; 

__attribute__((used)) static inline struct directive *next_inst(struct state *s) {
	int rd;
	struct directive *d = malloc (sizeof (*d));
	if (!d) {
		perror ("malloc()");
		return NULL;
	}
	memset (d, 0, sizeof (*d));
#if 0
	if (s->s_format)
		rd = read_text(s, d);
	else
#endif
	rd = read_bin (s, d);
	if (!rd) {
		free (d);
		return NULL;
	}

	return d;
}