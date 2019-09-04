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
struct TYPE_3__ {char* array; } ;
struct obs_lua_script {TYPE_1__ log_chunk; int /*<<< orphan*/  base; } ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 struct obs_lua_script* current_lua_script ; 
 int /*<<< orphan*/  dstr_copy (TYPE_1__*,char const*) ; 
 int /*<<< orphan*/  dstr_resize (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ lua_tointeger (int /*<<< orphan*/ *,int) ; 
 char* lua_tostring (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  script_log (int /*<<< orphan*/ *,int,char*,char const*) ; 
 char* strchr (char const*,char) ; 

__attribute__((used)) static int lua_script_log(lua_State *script)
{
	struct obs_lua_script *data = current_lua_script;
	int log_level = (int)lua_tointeger(script, 1);
	const char *msg = lua_tostring(script, 2);

	if (!msg)
		return 0;

	/* ------------------- */

	dstr_copy(&data->log_chunk, msg);

	const char *start = data->log_chunk.array;
	char *endl = strchr(start, '\n');

	while (endl) {
		*endl = 0;
		script_log(&data->base, log_level, "%s", start);
		*endl = '\n';

		start = endl + 1;
		endl = strchr(start, '\n');
	}

	if (start && *start)
		script_log(&data->base, log_level, "%s", start);
	dstr_resize(&data->log_chunk, 0);

	/* ------------------- */

	return 0;
}