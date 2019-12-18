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
typedef  int int16 ;
typedef  char bytea ;
typedef  int /*<<< orphan*/  StringInfoData ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  ERRCODE_INVALID_PARAMETER_VALUE ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  FrontendProtocol ; 
 char* OidOutputFunctionCall (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* OidSendFunctionCall (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int PG_PROTOCOL_MAJOR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VARDATA (char*) ; 
 int VARHDRSZ ; 
 int VARSIZE (char*) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,int) ; 
 int /*<<< orphan*/  getTypeBinaryOutputInfo (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  getTypeOutputInfo (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  pfree (char*) ; 
 int /*<<< orphan*/  pq_beginmessage (int /*<<< orphan*/ *,char) ; 
 int /*<<< orphan*/  pq_endmessage (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pq_sendbyte (int /*<<< orphan*/ *,char) ; 
 int /*<<< orphan*/  pq_sendbytes (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pq_sendcountedtext (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pq_sendint32 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  strlen (char*) ; 

__attribute__((used)) static void
SendFunctionResult(Datum retval, bool isnull, Oid rettype, int16 format)
{
	bool		newstyle = (PG_PROTOCOL_MAJOR(FrontendProtocol) >= 3);
	StringInfoData buf;

	pq_beginmessage(&buf, 'V');

	if (isnull)
	{
		if (newstyle)
			pq_sendint32(&buf, -1);
	}
	else
	{
		if (!newstyle)
			pq_sendbyte(&buf, 'G');

		if (format == 0)
		{
			Oid			typoutput;
			bool		typisvarlena;
			char	   *outputstr;

			getTypeOutputInfo(rettype, &typoutput, &typisvarlena);
			outputstr = OidOutputFunctionCall(typoutput, retval);
			pq_sendcountedtext(&buf, outputstr, strlen(outputstr), false);
			pfree(outputstr);
		}
		else if (format == 1)
		{
			Oid			typsend;
			bool		typisvarlena;
			bytea	   *outputbytes;

			getTypeBinaryOutputInfo(rettype, &typsend, &typisvarlena);
			outputbytes = OidSendFunctionCall(typsend, retval);
			pq_sendint32(&buf, VARSIZE(outputbytes) - VARHDRSZ);
			pq_sendbytes(&buf, VARDATA(outputbytes),
						 VARSIZE(outputbytes) - VARHDRSZ);
			pfree(outputbytes);
		}
		else
			ereport(ERROR,
					(errcode(ERRCODE_INVALID_PARAMETER_VALUE),
					 errmsg("unsupported format code: %d", format)));
	}

	if (!newstyle)
		pq_sendbyte(&buf, '0');

	pq_endmessage(&buf);
}