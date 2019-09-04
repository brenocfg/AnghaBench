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
struct match_state {char* pattern; scalar_t__ in_search; int /*<<< orphan*/  match_direction; } ;

/* Variables and functions */
 int /*<<< orphan*/  FIND_NEXT_MATCH_DOWN ; 
 int /*<<< orphan*/  FIND_NEXT_MATCH_UP ; 
 int KEY_BACKSPACE ; 
 int KEY_DOWN ; 
 int KEY_UP ; 
 int /*<<< orphan*/  MATCH_TINKER_PATTERN_DOWN ; 
 int /*<<< orphan*/  adj_match_dir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bzero (char*,int) ; 
 int /*<<< orphan*/  clrtoeol () ; 
 int get_mext_match (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ isalnum (char) ; 
 scalar_t__ isgraph (char) ; 
 int /*<<< orphan*/  move (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  refresh () ; 
 int strlen (char*) ; 

__attribute__((used)) static int do_match(int key, struct match_state *state, int *ans)
{
	char c = (char) key;
	int terminate_search = 0;
	*ans = -1;
	if (key == '/' || (state->in_search && key == 27)) {
		move(0, 0);
		refresh();
		clrtoeol();
		state->in_search = 1-state->in_search;
		bzero(state->pattern, sizeof(state->pattern));
		state->match_direction = MATCH_TINKER_PATTERN_DOWN;
		return 0;
	} else if (!state->in_search)
		return 1;

	if (isalnum(c) || isgraph(c) || c == ' ') {
		state->pattern[strlen(state->pattern)] = c;
		state->pattern[strlen(state->pattern)] = '\0';
		adj_match_dir(&state->match_direction);
		*ans = get_mext_match(state->pattern,
				state->match_direction);
	} else if (key == KEY_DOWN) {
		state->match_direction = FIND_NEXT_MATCH_DOWN;
		*ans = get_mext_match(state->pattern,
				state->match_direction);
	} else if (key == KEY_UP) {
		state->match_direction = FIND_NEXT_MATCH_UP;
		*ans = get_mext_match(state->pattern,
				state->match_direction);
	} else if (key == KEY_BACKSPACE || key == 127) {
		state->pattern[strlen(state->pattern)-1] = '\0';
		adj_match_dir(&state->match_direction);
	} else
		terminate_search = 1;

	if (terminate_search) {
		state->in_search = 0;
		bzero(state->pattern, sizeof(state->pattern));
		move(0, 0);
		refresh();
		clrtoeol();
		return -1;
	}
	return 0;
}