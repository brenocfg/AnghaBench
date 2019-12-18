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
typedef  union sctp_subtype {int dummy; } sctp_subtype ;
struct sctp_sm_table_entry {int (* fn ) (struct net*,struct sctp_endpoint*,struct sctp_association*,union sctp_subtype,void*,struct sctp_cmd_seq*) ;} ;
struct sctp_endpoint {int dummy; } ;
struct sctp_cmd_seq {int dummy; } ;
struct sctp_association {int dummy; } ;
struct net {int dummy; } ;
typedef  int /*<<< orphan*/  printfn_t ;
typedef  int /*<<< orphan*/  gfp_t ;
typedef  enum sctp_state { ____Placeholder_sctp_state } sctp_state ;
typedef  enum sctp_event_type { ____Placeholder_sctp_event_type } sctp_event_type ;
typedef  enum sctp_disposition { ____Placeholder_sctp_disposition } sctp_disposition ;

/* Variables and functions */
 int /*<<< orphan*/  debug_post_sfn () ; 
 int /*<<< orphan*/  debug_post_sfx () ; 
 int /*<<< orphan*/  debug_pre_sfn () ; 
#define  sctp_cname 131 
 int /*<<< orphan*/  sctp_init_cmd_seq (struct sctp_cmd_seq*) ; 
#define  sctp_oname 130 
#define  sctp_pname 129 
 int sctp_side_effects (int,union sctp_subtype,int,struct sctp_endpoint*,struct sctp_association**,void*,int,struct sctp_cmd_seq*,int /*<<< orphan*/ ) ; 
 struct sctp_sm_table_entry* sctp_sm_lookup_event (struct net*,int,int,union sctp_subtype) ; 
#define  sctp_tname 128 
 int stub2 (struct net*,struct sctp_endpoint*,struct sctp_association*,union sctp_subtype,void*,struct sctp_cmd_seq*) ; 

int sctp_do_sm(struct net *net, enum sctp_event_type event_type,
	       union sctp_subtype subtype, enum sctp_state state,
	       struct sctp_endpoint *ep, struct sctp_association *asoc,
	       void *event_arg, gfp_t gfp)
{
	typedef const char *(printfn_t)(union sctp_subtype);
	static printfn_t *table[] = {
		NULL, sctp_cname, sctp_tname, sctp_oname, sctp_pname,
	};
	printfn_t *debug_fn  __attribute__ ((unused)) = table[event_type];
	const struct sctp_sm_table_entry *state_fn;
	struct sctp_cmd_seq commands;
	enum sctp_disposition status;
	int error = 0;

	/* Look up the state function, run it, and then process the
	 * side effects.  These three steps are the heart of lksctp.
	 */
	state_fn = sctp_sm_lookup_event(net, event_type, state, subtype);

	sctp_init_cmd_seq(&commands);

	debug_pre_sfn();
	status = state_fn->fn(net, ep, asoc, subtype, event_arg, &commands);
	debug_post_sfn();

	error = sctp_side_effects(event_type, subtype, state,
				  ep, &asoc, event_arg, status,
				  &commands, gfp);
	debug_post_sfx();

	return error;
}