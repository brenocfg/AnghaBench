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
struct TYPE_2__ {int /*<<< orphan*/  encoding; } ;

/* Variables and functions */
 scalar_t__ PQmblen (char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ isalpha (unsigned char) ; 
 scalar_t__ pg_strncasecmp (char const*,char*,int) ; 
 TYPE_1__ pset ; 
 char* skip_white_space (char const*) ; 

__attribute__((used)) static bool
command_no_begin(const char *query)
{
	int			wordlen;

	/*
	 * First we must advance over any whitespace and comments.
	 */
	query = skip_white_space(query);

	/*
	 * Check word length (since "beginx" is not "begin").
	 */
	wordlen = 0;
	while (isalpha((unsigned char) query[wordlen]))
		wordlen += PQmblen(&query[wordlen], pset.encoding);

	/*
	 * Transaction control commands.  These should include every keyword that
	 * gives rise to a TransactionStmt in the backend grammar, except for the
	 * savepoint-related commands.
	 *
	 * (We assume that START must be START TRANSACTION, since there is
	 * presently no other "START foo" command.)
	 */
	if (wordlen == 5 && pg_strncasecmp(query, "abort", 5) == 0)
		return true;
	if (wordlen == 5 && pg_strncasecmp(query, "begin", 5) == 0)
		return true;
	if (wordlen == 5 && pg_strncasecmp(query, "start", 5) == 0)
		return true;
	if (wordlen == 6 && pg_strncasecmp(query, "commit", 6) == 0)
		return true;
	if (wordlen == 3 && pg_strncasecmp(query, "end", 3) == 0)
		return true;
	if (wordlen == 8 && pg_strncasecmp(query, "rollback", 8) == 0)
		return true;
	if (wordlen == 7 && pg_strncasecmp(query, "prepare", 7) == 0)
	{
		/* PREPARE TRANSACTION is a TC command, PREPARE foo is not */
		query += wordlen;

		query = skip_white_space(query);

		wordlen = 0;
		while (isalpha((unsigned char) query[wordlen]))
			wordlen += PQmblen(&query[wordlen], pset.encoding);

		if (wordlen == 11 && pg_strncasecmp(query, "transaction", 11) == 0)
			return true;
		return false;
	}

	/*
	 * Commands not allowed within transactions.  The statements checked for
	 * here should be exactly those that call PreventInTransactionBlock() in
	 * the backend.
	 */
	if (wordlen == 6 && pg_strncasecmp(query, "vacuum", 6) == 0)
		return true;
	if (wordlen == 7 && pg_strncasecmp(query, "cluster", 7) == 0)
	{
		/* CLUSTER with any arguments is allowed in transactions */
		query += wordlen;

		query = skip_white_space(query);

		if (isalpha((unsigned char) query[0]))
			return false;		/* has additional words */
		return true;			/* it's CLUSTER without arguments */
	}

	if (wordlen == 6 && pg_strncasecmp(query, "create", 6) == 0)
	{
		query += wordlen;

		query = skip_white_space(query);

		wordlen = 0;
		while (isalpha((unsigned char) query[wordlen]))
			wordlen += PQmblen(&query[wordlen], pset.encoding);

		if (wordlen == 8 && pg_strncasecmp(query, "database", 8) == 0)
			return true;
		if (wordlen == 10 && pg_strncasecmp(query, "tablespace", 10) == 0)
			return true;

		/* CREATE [UNIQUE] INDEX CONCURRENTLY isn't allowed in xacts */
		if (wordlen == 6 && pg_strncasecmp(query, "unique", 6) == 0)
		{
			query += wordlen;

			query = skip_white_space(query);

			wordlen = 0;
			while (isalpha((unsigned char) query[wordlen]))
				wordlen += PQmblen(&query[wordlen], pset.encoding);
		}

		if (wordlen == 5 && pg_strncasecmp(query, "index", 5) == 0)
		{
			query += wordlen;

			query = skip_white_space(query);

			wordlen = 0;
			while (isalpha((unsigned char) query[wordlen]))
				wordlen += PQmblen(&query[wordlen], pset.encoding);

			if (wordlen == 12 && pg_strncasecmp(query, "concurrently", 12) == 0)
				return true;
		}

		return false;
	}

	if (wordlen == 5 && pg_strncasecmp(query, "alter", 5) == 0)
	{
		query += wordlen;

		query = skip_white_space(query);

		wordlen = 0;
		while (isalpha((unsigned char) query[wordlen]))
			wordlen += PQmblen(&query[wordlen], pset.encoding);

		/* ALTER SYSTEM isn't allowed in xacts */
		if (wordlen == 6 && pg_strncasecmp(query, "system", 6) == 0)
			return true;

		return false;
	}

	/*
	 * Note: these tests will match DROP SYSTEM and REINDEX TABLESPACE, which
	 * aren't really valid commands so we don't care much. The other four
	 * possible matches are correct.
	 */
	if ((wordlen == 4 && pg_strncasecmp(query, "drop", 4) == 0) ||
		(wordlen == 7 && pg_strncasecmp(query, "reindex", 7) == 0))
	{
		query += wordlen;

		query = skip_white_space(query);

		wordlen = 0;
		while (isalpha((unsigned char) query[wordlen]))
			wordlen += PQmblen(&query[wordlen], pset.encoding);

		if (wordlen == 8 && pg_strncasecmp(query, "database", 8) == 0)
			return true;
		if (wordlen == 6 && pg_strncasecmp(query, "system", 6) == 0)
			return true;
		if (wordlen == 10 && pg_strncasecmp(query, "tablespace", 10) == 0)
			return true;
		if (wordlen == 5 && (pg_strncasecmp(query, "index", 5) == 0 ||
							 pg_strncasecmp(query, "table", 5) == 0))
		{
			query += wordlen;
			query = skip_white_space(query);
			wordlen = 0;
			while (isalpha((unsigned char) query[wordlen]))
				wordlen += PQmblen(&query[wordlen], pset.encoding);

			/*
			 * REINDEX [ TABLE | INDEX ] CONCURRENTLY are not allowed in
			 * xacts.
			 */
			if (wordlen == 12 && pg_strncasecmp(query, "concurrently", 12) == 0)
				return true;
		}

		/* DROP INDEX CONCURRENTLY isn't allowed in xacts */
		if (wordlen == 5 && pg_strncasecmp(query, "index", 5) == 0)
		{
			query += wordlen;

			query = skip_white_space(query);

			wordlen = 0;
			while (isalpha((unsigned char) query[wordlen]))
				wordlen += PQmblen(&query[wordlen], pset.encoding);

			if (wordlen == 12 && pg_strncasecmp(query, "concurrently", 12) == 0)
				return true;

			return false;
		}

		return false;
	}

	/* DISCARD ALL isn't allowed in xacts, but other variants are allowed. */
	if (wordlen == 7 && pg_strncasecmp(query, "discard", 7) == 0)
	{
		query += wordlen;

		query = skip_white_space(query);

		wordlen = 0;
		while (isalpha((unsigned char) query[wordlen]))
			wordlen += PQmblen(&query[wordlen], pset.encoding);

		if (wordlen == 3 && pg_strncasecmp(query, "all", 3) == 0)
			return true;
		return false;
	}

	return false;
}