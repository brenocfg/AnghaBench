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
struct TYPE_2__ {int id; } ;
union jr_entry {TYPE_1__ prefix; } ;
struct jit_buf_desc {int dummy; } ;

/* Variables and functions */
#define  JIT_CODE_DEBUG_INFO 131 
#define  JIT_CODE_LOAD 130 
#define  JIT_CODE_MOVE 129 
#define  JIT_CODE_UNWINDING_INFO 128 
 union jr_entry* jit_get_next_entry (struct jit_buf_desc*) ; 
 int jit_repipe_code_load (struct jit_buf_desc*,union jr_entry*) ; 
 int jit_repipe_code_move (struct jit_buf_desc*,union jr_entry*) ; 
 int jit_repipe_debug_info (struct jit_buf_desc*,union jr_entry*) ; 
 int jit_repipe_unwinding_info (struct jit_buf_desc*,union jr_entry*) ; 

__attribute__((used)) static int
jit_process_dump(struct jit_buf_desc *jd)
{
	union jr_entry *jr;
	int ret = 0;

	while ((jr = jit_get_next_entry(jd))) {
		switch(jr->prefix.id) {
		case JIT_CODE_LOAD:
			ret = jit_repipe_code_load(jd, jr);
			break;
		case JIT_CODE_MOVE:
			ret = jit_repipe_code_move(jd, jr);
			break;
		case JIT_CODE_DEBUG_INFO:
			ret = jit_repipe_debug_info(jd, jr);
			break;
		case JIT_CODE_UNWINDING_INFO:
			ret = jit_repipe_unwinding_info(jd, jr);
			break;
		default:
			ret = 0;
			continue;
		}
	}
	return ret;
}