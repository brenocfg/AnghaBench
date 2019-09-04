#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_char ;
struct TYPE_3__ {int value; } ;
struct TYPE_4__ {TYPE_1__ n; } ;
struct var_t {TYPE_2__ u; } ;
struct st_var_header {scalar_t__ var_type; char* name; struct var_t* data; } ;
typedef  int /*<<< orphan*/  num_buf ;

/* Variables and functions */
 int E_DEC ; 
 int E_INC ; 
 int FIRST_SET_VAR ; 
 char SPACE ; 
 scalar_t__ VAR_NUM ; 
 int VAR_START ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int /*<<< orphan*/  spk_close_press ; 
 struct st_var_header* spk_get_var_header (int) ; 
 scalar_t__ spk_set_num_var (int,struct st_var_header*,int) ; 
 int /*<<< orphan*/  synth_printf (char*,char*) ; 

__attribute__((used)) static int inc_dec_var(u_char value)
{
	struct st_var_header *p_header;
	struct var_t *var_data;
	char num_buf[32];
	char *cp = num_buf;
	char *pn;
	int var_id = (int)value - VAR_START;
	int how = (var_id & 1) ? E_INC : E_DEC;

	var_id = var_id / 2 + FIRST_SET_VAR;
	p_header = spk_get_var_header(var_id);
	if (!p_header)
		return -1;
	if (p_header->var_type != VAR_NUM)
		return -1;
	var_data = p_header->data;
	if (spk_set_num_var(1, p_header, how) != 0)
		return -1;
	if (!spk_close_press) {
		for (pn = p_header->name; *pn; pn++) {
			if (*pn == '_')
				*cp = SPACE;
			else
				*cp++ = *pn;
		}
	}
	snprintf(cp, sizeof(num_buf) - (cp - num_buf), " %d ",
		 var_data->u.n.value);
	synth_printf("%s", num_buf);
	return 0;
}