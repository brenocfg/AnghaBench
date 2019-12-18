#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {char const* key; char* val; } ;
typedef  TYPE_2__ xml_element_attr ;
struct TYPE_7__ {int /*<<< orphan*/  len; int /*<<< orphan*/  str; } ;
struct TYPE_9__ {char* name; int /*<<< orphan*/  children; TYPE_1__ text; int /*<<< orphan*/  attrs; } ;
typedef  TYPE_3__ xml_element ;
struct buffer_st {int /*<<< orphan*/  offset; int /*<<< orphan*/  data; } ;
struct array_info {char* kids_type; } ;
typedef  void* XMLRPC_VALUE ;
typedef  scalar_t__ XMLRPC_REQUEST_TYPE ;
typedef  int /*<<< orphan*/  XMLRPC_REQUEST ;

/* Variables and functions */
 TYPE_2__* Q_Head (int /*<<< orphan*/ *) ; 
 TYPE_2__* Q_Next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Q_Size (int /*<<< orphan*/ *) ; 
 char* TOKEN_ACTOR ; 
 char* TOKEN_ACTOR_NEXT ; 
 char* TOKEN_ARRAY ; 
 char* TOKEN_ARRAY_TYPE ; 
 char* TOKEN_BASE64 ; 
 char* TOKEN_BOOLEAN ; 
 char* TOKEN_DATETIME ; 
 char* TOKEN_DOUBLE ; 
 char* TOKEN_FLOAT ; 
 char* TOKEN_INT ; 
 char* TOKEN_MUSTUNDERSTAND ; 
 char* TOKEN_NULL ; 
 char* TOKEN_STRING ; 
 char* TOKEN_STRUCT ; 
 char* TOKEN_TYPE ; 
 int /*<<< orphan*/  XMLRPC_AddValueToVector (void*,void*) ; 
 void* XMLRPC_CreateValueEmpty () ; 
 scalar_t__ XMLRPC_GetVectorType (void*) ; 
 int /*<<< orphan*/  XMLRPC_RequestGetError (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XMLRPC_RequestSetError (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XMLRPC_RequestSetMethodName (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  XMLRPC_RequestSetRequestType (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  XMLRPC_SetIsVector (void*,scalar_t__) ; 
 int /*<<< orphan*/  XMLRPC_SetValueBase64 (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XMLRPC_SetValueBoolean (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XMLRPC_SetValueDateTime_ISO8601 (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XMLRPC_SetValueDouble (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XMLRPC_SetValueID_Case (void*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XMLRPC_SetValueInt (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XMLRPC_SetValueString (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atof (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atoi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  base64_decode_xmlrpc (struct buffer_st*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  buffer_delete (struct buffer_st*) ; 
 int /*<<< orphan*/  efree (struct array_info*) ; 
 int /*<<< orphan*/  gen_soap_fault (char*,char*,char*,char*) ; 
 scalar_t__ is_soap_type (char*) ; 
 struct array_info* parse_array_type_info (char const*) ; 
 scalar_t__ strcasestr (char*,char*) ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 scalar_t__ strstr (char*,char*) ; 
 int /*<<< orphan*/  xmlrpc_case_exact ; 
 scalar_t__ xmlrpc_request_call ; 
 scalar_t__ xmlrpc_request_none ; 
 scalar_t__ xmlrpc_request_response ; 
 scalar_t__ xmlrpc_vector_array ; 
 scalar_t__ xmlrpc_vector_mixed ; 
 scalar_t__ xmlrpc_vector_struct ; 

XMLRPC_VALUE xml_element_to_SOAP_REQUEST_worker(XMLRPC_REQUEST request,
																XMLRPC_VALUE xParent,
																struct array_info* parent_array,
																XMLRPC_VALUE xCurrent,
																xml_element* el,
																int depth) {
	XMLRPC_REQUEST_TYPE rtype = xmlrpc_request_none;

	/* no current element on first call */
	if (!xCurrent) {
		xCurrent = XMLRPC_CreateValueEmpty();
	}

	/* increment recursion depth gauge */
	depth ++;

	/* safety first. must have a valid element */
	if (el && el->name) {
		const char* id = NULL;
		const char* type = NULL, *arrayType=NULL, *actor = NULL;
		xml_element_attr* attr_iter = Q_Head(&el->attrs);
		int b_must_understand = 0;

		/* in soap, types may be specified in either element name -or- with xsi:type attribute. */
		if (is_soap_type(el->name)) {
			type = el->name;
		}
		/* if our parent node, by definition a vector, is not an array, then
		   our element name must be our key identifier. */
		else if (XMLRPC_GetVectorType(xParent) != xmlrpc_vector_array) {
			id = el->name;
			if(!strcmp(id, "item")) {
			}
		}

		/* iterate through element attributes, pick out useful stuff. */
		while (attr_iter) {
			/* element's type */
			if (!strcmp(attr_iter->key, TOKEN_TYPE)) {
				type = attr_iter->val;
			}
			/* array type */
			else if (!strcmp(attr_iter->key, TOKEN_ARRAY_TYPE)) {
				arrayType = attr_iter->val;
			}
			/* must understand, sometimes present in headers. */
			else if (!strcmp(attr_iter->key, TOKEN_MUSTUNDERSTAND)) {
				b_must_understand = strchr(attr_iter->val, '1') ? 1 : 0;
			}
			/* actor, used in conjunction with must understand. */
			else if (!strcmp(attr_iter->key, TOKEN_ACTOR)) {
				actor = attr_iter->val;
			}
			attr_iter = Q_Next(&el->attrs);
		}

		/* check if caller says we must understand something in a header. */
		if (b_must_understand) {
			/* is must understand actually indended for us?
			   BUG: spec says we should also determine if actor is our URL, but
			        we do not have that information. */
			if (!actor || !strcmp(actor, TOKEN_ACTOR_NEXT)) {
				/* TODO: implement callbacks or other mechanism for applications
				   to "understand" these headers. For now, we just bail if we
				   get a mustUnderstand header intended for us. */
				XMLRPC_RequestSetError(request,
											  gen_soap_fault("SOAP-ENV:MustUnderstand",
																  "SOAP Must Understand Error",
																  "", ""));
				return xCurrent;
			}
		}

		/* set id (key) if one was found. */
		if (id) {
			XMLRPC_SetValueID_Case(xCurrent, id, 0, xmlrpc_case_exact);
		}

		/* according to soap spec,
		   depth 1 = Envelope, 2 = Header, Body & Fault, 3 = methodcall or response. */
		if (depth == 3) {
			const char* methodname = el->name;
			char* p = NULL;

			/* BUG: we determine request or response type using presence of "Response" in element name.
			   According to spec, this is only recommended, not required. Apparently, implementations
			   are supposed to know the type of action based on state, which strikes me as a bit lame.
			   Anyway, we don't have that state info, thus we use Response as a heuristic. */
			rtype =
#ifdef strcasestr
			strcasestr(el->name, "response") ? xmlrpc_request_response : xmlrpc_request_call;
#else
			strstr(el->name, "esponse") ? xmlrpc_request_response : xmlrpc_request_call;
#endif
			XMLRPC_RequestSetRequestType(request, rtype);

			/* Get methodname.  strip xml namespace crap. */
			p = strchr(el->name, ':');
			if (p) {
				methodname = p + 1;
			}
			if (rtype == xmlrpc_request_call) {
				XMLRPC_RequestSetMethodName(request, methodname);
			}
		}


		/* Next, we begin to convert actual values. if no children, then must be a scalar value. */
		if (!Q_Size(&el->children)) {
			if (!type && parent_array && parent_array->kids_type[0]) {
				type = parent_array->kids_type;
			}
			if (!type || !strcmp(type, TOKEN_STRING)) {
				XMLRPC_SetValueString(xCurrent, el->text.str, el->text.len);
			}
			else if (!strcmp(type, TOKEN_INT)) {
				XMLRPC_SetValueInt(xCurrent, atoi(el->text.str));
			}
			else if (!strcmp(type, TOKEN_BOOLEAN)) {
				XMLRPC_SetValueBoolean(xCurrent, atoi(el->text.str));
			}
			else if (!strcmp(type, TOKEN_DOUBLE) ||
						!strcmp(type, TOKEN_FLOAT)) {
				XMLRPC_SetValueDouble(xCurrent, atof(el->text.str));
			}
			else if (!strcmp(type, TOKEN_NULL)) {
				/* already an empty val. do nothing. */
			}
			else if (!strcmp(type, TOKEN_DATETIME)) {
				XMLRPC_SetValueDateTime_ISO8601(xCurrent, el->text.str);
			}
			else if (!strcmp(type, TOKEN_BASE64)) {
				struct buffer_st buf;
				base64_decode_xmlrpc(&buf, el->text.str, el->text.len);
				XMLRPC_SetValueBase64(xCurrent, buf.data, buf.offset);
				buffer_delete(&buf);
			}
		}
		/* Element has children, thus a vector, or "compound type" in soap-speak. */
		else {
			struct array_info* ai = NULL;
			xml_element* iter = (xml_element*)Q_Head(&el->children);

			if (!type || !strcmp(type, TOKEN_STRUCT)) {
				XMLRPC_SetIsVector(xCurrent, xmlrpc_vector_struct);
			}
			else if (!strcmp(type, TOKEN_ARRAY) || arrayType != NULL) {
				/* determine magic associated with soap array type.
				   this is passed down as we recurse, so our children have access to the info. */
				ai = parse_array_type_info(arrayType);	/* alloc'ed ai free'd below. */
				XMLRPC_SetIsVector(xCurrent, xmlrpc_vector_array);
			}
			else {
				/* mixed is probably closest thing we have to compound type. */
				XMLRPC_SetIsVector(xCurrent, xmlrpc_vector_mixed);
			}
			/* Recurse, adding values as we go.  Check for error during recursion
			   and if found, bail.  this short-circuits us out of the recursion. */
			while ( iter && !XMLRPC_RequestGetError(request) ) {
				XMLRPC_VALUE xNext = NULL;
				/* top level elements don't actually represent values, so we just pass the
				   current value along until we are deep enough. */
				if ( depth <= 2 ||
					  (rtype == xmlrpc_request_response && depth <= 3) ) {
					xml_element_to_SOAP_REQUEST_worker(request, NULL, ai, xCurrent, iter, depth);
				}
				/* ready to do some actual de-serialization. create a new empty value and
				   pass that along to be init'd, then add it to our current vector. */
				else {
					xNext = XMLRPC_CreateValueEmpty();
					xml_element_to_SOAP_REQUEST_worker(request, xCurrent, ai, xNext, iter, depth);
					XMLRPC_AddValueToVector(xCurrent, xNext);
				}
				iter = (xml_element*)Q_Next(&el->children);
			}
			/* cleanup */
			if (ai) {
				efree(ai);
			}
		}
	}
	return xCurrent;
}