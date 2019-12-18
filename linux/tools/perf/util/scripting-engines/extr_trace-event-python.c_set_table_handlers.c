#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_6__ {int /*<<< orphan*/ * cpr; TYPE_3__* crp; } ;
struct tables {int db_export_mode; int /*<<< orphan*/  synth_handler; TYPE_2__ dbe; } ;
struct TYPE_7__ {int /*<<< orphan*/ * cpr; } ;
struct TYPE_5__ {int priv_size; } ;
typedef  int /*<<< orphan*/  PyObject ;

/* Variables and functions */
 int /*<<< orphan*/ * PyDict_GetItemString (int /*<<< orphan*/ ,char const*) ; 
 int PyObject_IsTrue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_FatalError (char*) ; 
 int /*<<< orphan*/  SET_TABLE_HANDLER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  branch_type ; 
 int /*<<< orphan*/  call_path ; 
 int /*<<< orphan*/ * call_path_root__new () ; 
 int /*<<< orphan*/  call_return ; 
 TYPE_3__* call_return_processor__new (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  comm ; 
 int /*<<< orphan*/  comm_thread ; 
 int /*<<< orphan*/  context_switch ; 
 scalar_t__ db_export__init (TYPE_2__*) ; 
 int /*<<< orphan*/  dso ; 
 int /*<<< orphan*/  evsel ; 
 int /*<<< orphan*/  get_handler (char*) ; 
 int /*<<< orphan*/  handler_call_die (char const*) ; 
 int /*<<< orphan*/  machine ; 
 int /*<<< orphan*/  main_dict ; 
 int /*<<< orphan*/  memset (struct tables*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  python_process_call_return ; 
 int /*<<< orphan*/  sample ; 
 int /*<<< orphan*/  symbol ; 
 TYPE_1__ symbol_conf ; 
 int /*<<< orphan*/  thread ; 

__attribute__((used)) static void set_table_handlers(struct tables *tables)
{
	const char *perf_db_export_mode = "perf_db_export_mode";
	const char *perf_db_export_calls = "perf_db_export_calls";
	const char *perf_db_export_callchains = "perf_db_export_callchains";
	PyObject *db_export_mode, *db_export_calls, *db_export_callchains;
	bool export_calls = false;
	bool export_callchains = false;
	int ret;

	memset(tables, 0, sizeof(struct tables));
	if (db_export__init(&tables->dbe))
		Py_FatalError("failed to initialize export");

	db_export_mode = PyDict_GetItemString(main_dict, perf_db_export_mode);
	if (!db_export_mode)
		return;

	ret = PyObject_IsTrue(db_export_mode);
	if (ret == -1)
		handler_call_die(perf_db_export_mode);
	if (!ret)
		return;

	/* handle export calls */
	tables->dbe.crp = NULL;
	db_export_calls = PyDict_GetItemString(main_dict, perf_db_export_calls);
	if (db_export_calls) {
		ret = PyObject_IsTrue(db_export_calls);
		if (ret == -1)
			handler_call_die(perf_db_export_calls);
		export_calls = !!ret;
	}

	if (export_calls) {
		tables->dbe.crp =
			call_return_processor__new(python_process_call_return,
						   &tables->dbe);
		if (!tables->dbe.crp)
			Py_FatalError("failed to create calls processor");
	}

	/* handle export callchains */
	tables->dbe.cpr = NULL;
	db_export_callchains = PyDict_GetItemString(main_dict,
						    perf_db_export_callchains);
	if (db_export_callchains) {
		ret = PyObject_IsTrue(db_export_callchains);
		if (ret == -1)
			handler_call_die(perf_db_export_callchains);
		export_callchains = !!ret;
	}

	if (export_callchains) {
		/*
		 * Attempt to use the call path root from the call return
		 * processor, if the call return processor is in use. Otherwise,
		 * we allocate a new call path root. This prevents exporting
		 * duplicate call path ids when both are in use simultaniously.
		 */
		if (tables->dbe.crp)
			tables->dbe.cpr = tables->dbe.crp->cpr;
		else
			tables->dbe.cpr = call_path_root__new();

		if (!tables->dbe.cpr)
			Py_FatalError("failed to create call path root");
	}

	tables->db_export_mode = true;
	/*
	 * Reserve per symbol space for symbol->db_id via symbol__priv()
	 */
	symbol_conf.priv_size = sizeof(u64);

	SET_TABLE_HANDLER(evsel);
	SET_TABLE_HANDLER(machine);
	SET_TABLE_HANDLER(thread);
	SET_TABLE_HANDLER(comm);
	SET_TABLE_HANDLER(comm_thread);
	SET_TABLE_HANDLER(dso);
	SET_TABLE_HANDLER(symbol);
	SET_TABLE_HANDLER(branch_type);
	SET_TABLE_HANDLER(sample);
	SET_TABLE_HANDLER(call_path);
	SET_TABLE_HANDLER(call_return);
	SET_TABLE_HANDLER(context_switch);

	/*
	 * Synthesized events are samples but with architecture-specific data
	 * stored in sample->raw_data. They are exported via
	 * python_export_sample() and consequently do not need a separate export
	 * callback.
	 */
	tables->synth_handler = get_handler("synth_data");
}