#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct msrmap {char* pname; } ;
struct TYPE_11__ {scalar_t__ type; int size; } ;
typedef  TYPE_1__ jsmntok_t ;

/* Variables and functions */
 int EIO ; 
 int ENOENT ; 
 int /*<<< orphan*/  EXPECT (int,TYPE_1__*,char*) ; 
 scalar_t__ JSMN_ARRAY ; 
 scalar_t__ JSMN_OBJECT ; 
 scalar_t__ JSMN_STRING ; 
 int /*<<< orphan*/  addfield (char*,char**,char*,char*,TYPE_1__*) ; 
 char* field_to_perf (int /*<<< orphan*/ ,char*,TYPE_1__*) ; 
 int /*<<< orphan*/  fixdesc (char*) ; 
 int /*<<< orphan*/  fixname (char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  free_json (char*,size_t,TYPE_1__*) ; 
 scalar_t__ json_streq (char*,TYPE_1__*,char*) ; 
 struct msrmap* lookup_msr (char*,TYPE_1__*) ; 
 scalar_t__ match_field (char*,TYPE_1__*,int,char**,TYPE_1__*) ; 
 TYPE_1__* parse_json (char const*,char**,size_t*,int*) ; 
 char* real_event (char*,char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,unsigned long long) ; 
 char* strdup (char const*) ; 
 int /*<<< orphan*/  strstr (char*,char*) ; 
 int strtoul (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char tolower (char) ; 
 int try_fixup (char const*,char*,char**,char**,char**,char**,char**,char**,char**,char**,char**,char**,char**,unsigned long long) ; 
 int /*<<< orphan*/  unit_to_pmu ; 

int json_events(const char *fn,
	  int (*func)(void *data, char *name, char *event, char *desc,
		      char *long_desc,
		      char *pmu, char *unit, char *perpkg,
		      char *metric_expr,
		      char *metric_name, char *metric_group),
	  void *data)
{
	int err;
	size_t size;
	jsmntok_t *tokens, *tok;
	int i, j, len;
	char *map;
	char buf[128];

	if (!fn)
		return -ENOENT;

	tokens = parse_json(fn, &map, &size, &len);
	if (!tokens)
		return -EIO;
	EXPECT(tokens->type == JSMN_ARRAY, tokens, "expected top level array");
	tok = tokens + 1;
	for (i = 0; i < tokens->size; i++) {
		char *event = NULL, *desc = NULL, *name = NULL;
		char *long_desc = NULL;
		char *extra_desc = NULL;
		char *pmu = NULL;
		char *filter = NULL;
		char *perpkg = NULL;
		char *unit = NULL;
		char *metric_expr = NULL;
		char *metric_name = NULL;
		char *metric_group = NULL;
		char *arch_std = NULL;
		unsigned long long eventcode = 0;
		struct msrmap *msr = NULL;
		jsmntok_t *msrval = NULL;
		jsmntok_t *precise = NULL;
		jsmntok_t *obj = tok++;

		EXPECT(obj->type == JSMN_OBJECT, obj, "expected object");
		for (j = 0; j < obj->size; j += 2) {
			jsmntok_t *field, *val;
			int nz;
			char *s;

			field = tok + j;
			EXPECT(field->type == JSMN_STRING, tok + j,
			       "Expected field name");
			val = tok + j + 1;
			EXPECT(val->type == JSMN_STRING, tok + j + 1,
			       "Expected string value");

			nz = !json_streq(map, val, "0");
			if (match_field(map, field, nz, &event, val)) {
				/* ok */
			} else if (json_streq(map, field, "EventCode")) {
				char *code = NULL;
				addfield(map, &code, "", "", val);
				eventcode |= strtoul(code, NULL, 0);
				free(code);
			} else if (json_streq(map, field, "ExtSel")) {
				char *code = NULL;
				addfield(map, &code, "", "", val);
				eventcode |= strtoul(code, NULL, 0) << 21;
				free(code);
			} else if (json_streq(map, field, "EventName")) {
				addfield(map, &name, "", "", val);
			} else if (json_streq(map, field, "BriefDescription")) {
				addfield(map, &desc, "", "", val);
				fixdesc(desc);
			} else if (json_streq(map, field,
					     "PublicDescription")) {
				addfield(map, &long_desc, "", "", val);
				fixdesc(long_desc);
			} else if (json_streq(map, field, "PEBS") && nz) {
				precise = val;
			} else if (json_streq(map, field, "MSRIndex") && nz) {
				msr = lookup_msr(map, val);
			} else if (json_streq(map, field, "MSRValue")) {
				msrval = val;
			} else if (json_streq(map, field, "Errata") &&
				   !json_streq(map, val, "null")) {
				addfield(map, &extra_desc, ". ",
					" Spec update: ", val);
			} else if (json_streq(map, field, "Data_LA") && nz) {
				addfield(map, &extra_desc, ". ",
					" Supports address when precise",
					NULL);
			} else if (json_streq(map, field, "Unit")) {
				const char *ppmu;

				ppmu = field_to_perf(unit_to_pmu, map, val);
				if (ppmu) {
					pmu = strdup(ppmu);
				} else {
					if (!pmu)
						pmu = strdup("uncore_");
					addfield(map, &pmu, "", "", val);
					for (s = pmu; *s; s++)
						*s = tolower(*s);
				}
				addfield(map, &desc, ". ", "Unit: ", NULL);
				addfield(map, &desc, "", pmu, NULL);
				addfield(map, &desc, "", " ", NULL);
			} else if (json_streq(map, field, "Filter")) {
				addfield(map, &filter, "", "", val);
			} else if (json_streq(map, field, "ScaleUnit")) {
				addfield(map, &unit, "", "", val);
			} else if (json_streq(map, field, "PerPkg")) {
				addfield(map, &perpkg, "", "", val);
			} else if (json_streq(map, field, "MetricName")) {
				addfield(map, &metric_name, "", "", val);
			} else if (json_streq(map, field, "MetricGroup")) {
				addfield(map, &metric_group, "", "", val);
			} else if (json_streq(map, field, "MetricExpr")) {
				addfield(map, &metric_expr, "", "", val);
				for (s = metric_expr; *s; s++)
					*s = tolower(*s);
			} else if (json_streq(map, field, "ArchStdEvent")) {
				addfield(map, &arch_std, "", "", val);
				for (s = arch_std; *s; s++)
					*s = tolower(*s);
			}
			/* ignore unknown fields */
		}
		if (precise && desc && !strstr(desc, "(Precise Event)")) {
			if (json_streq(map, precise, "2"))
				addfield(map, &extra_desc, " ",
						"(Must be precise)", NULL);
			else
				addfield(map, &extra_desc, " ",
						"(Precise event)", NULL);
		}
		snprintf(buf, sizeof buf, "event=%#llx", eventcode);
		addfield(map, &event, ",", buf, NULL);
		if (desc && extra_desc)
			addfield(map, &desc, " ", extra_desc, NULL);
		if (long_desc && extra_desc)
			addfield(map, &long_desc, " ", extra_desc, NULL);
		if (filter)
			addfield(map, &event, ",", filter, NULL);
		if (msr != NULL)
			addfield(map, &event, ",", msr->pname, msrval);
		if (name)
			fixname(name);

		if (arch_std) {
			/*
			 * An arch standard event is referenced, so try to
			 * fixup any unassigned values.
			 */
			err = try_fixup(fn, arch_std, &event, &desc, &name,
					&long_desc, &pmu, &filter, &perpkg,
					&unit, &metric_expr, &metric_name,
					&metric_group, eventcode);
			if (err)
				goto free_strings;
		}
		err = func(data, name, real_event(name, event), desc, long_desc,
			   pmu, unit, perpkg, metric_expr, metric_name, metric_group);
free_strings:
		free(event);
		free(desc);
		free(name);
		free(long_desc);
		free(extra_desc);
		free(pmu);
		free(filter);
		free(perpkg);
		free(unit);
		free(metric_expr);
		free(metric_name);
		free(metric_group);
		free(arch_std);

		if (err)
			break;
		tok += j;
	}
	EXPECT(tok - tokens == len, tok, "unexpected objects at end");
	err = 0;
out_free:
	free_json(map, size, tokens);
	return err;
}