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
struct state {int dummy; } ;

/* Variables and functions */
 struct state _state ; 
 int /*<<< orphan*/  memset (struct state*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline struct state *get_state(void) {
	memset (&_state, 0, sizeof (struct state));
	return &_state;
}