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
struct younow_mem_struct {char const* memory; scalar_t__ size; } ;
struct dstr {void* array; } ;
typedef  scalar_t__ CURLcode ;
typedef  int /*<<< orphan*/  CURL ;

/* Variables and functions */
 scalar_t__ CURLE_OK ; 
 int /*<<< orphan*/  CURLINFO_RESPONSE_CODE ; 
 int /*<<< orphan*/  CURLOPT_SSL_ENABLE_ALPN ; 
 int /*<<< orphan*/  CURLOPT_SSL_VERIFYHOST ; 
 int /*<<< orphan*/  CURLOPT_SSL_VERIFYPEER ; 
 int /*<<< orphan*/  CURLOPT_TIMEOUT ; 
 int /*<<< orphan*/  CURLOPT_URL ; 
 int /*<<< orphan*/  CURLOPT_WRITEDATA ; 
 int /*<<< orphan*/  CURLOPT_WRITEFUNCTION ; 
 int /*<<< orphan*/  LOG_INFO ; 
 int /*<<< orphan*/  LOG_WARNING ; 
 int /*<<< orphan*/  blog (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  curl_easy_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  curl_easy_getinfo (int /*<<< orphan*/ *,int /*<<< orphan*/ ,long*) ; 
 int /*<<< orphan*/ * curl_easy_init () ; 
 scalar_t__ curl_easy_perform (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  curl_easy_setopt (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*) ; 
 char const* curl_easy_strerror (scalar_t__) ; 
 char const* current_ingest ; 
 int /*<<< orphan*/  dstr_copy (struct dstr*,char const*) ; 
 int /*<<< orphan*/  dstr_free (struct dstr*) ; 
 int /*<<< orphan*/  dstr_init (struct dstr*) ; 
 int /*<<< orphan*/  dstr_ncat (struct dstr*,char const*,int) ; 
 int /*<<< orphan*/  free (char const*) ; 
 char const* malloc (int) ; 
 char* strchr (char const*,char) ; 
 char* strdup (char const*) ; 
 void* younow_write_cb ; 

const char *younow_get_ingest(const char *server, const char *key)
{
	CURL *curl_handle;
	CURLcode res;
	struct younow_mem_struct chunk;
	struct dstr uri;
	long response_code;

	// find the delimiter in stream key
	const char *delim = strchr(key, '_');
	if (delim == NULL) {
		blog(LOG_WARNING,
		     "younow_get_ingest: delimiter not found in stream key");
		return server;
	}

	curl_handle = curl_easy_init();

	chunk.memory = malloc(1); /* will be grown as needed by realloc */
	chunk.size = 0;           /* no data at this point */

	dstr_init(&uri);
	dstr_copy(&uri, server);
	dstr_ncat(&uri, key, delim - key);

	curl_easy_setopt(curl_handle, CURLOPT_URL, uri.array);
	curl_easy_setopt(curl_handle, CURLOPT_SSL_VERIFYPEER, true);
	curl_easy_setopt(curl_handle, CURLOPT_SSL_VERIFYHOST, 2L);
	curl_easy_setopt(curl_handle, CURLOPT_TIMEOUT, 3L);
	curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, younow_write_cb);
	curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, (void *)&chunk);

#if LIBCURL_VERSION_NUM >= 0x072400
	// A lot of servers don't yet support ALPN
	curl_easy_setopt(curl_handle, CURLOPT_SSL_ENABLE_ALPN, 0);
#endif

	res = curl_easy_perform(curl_handle);
	dstr_free(&uri);

	if (res != CURLE_OK) {
		blog(LOG_WARNING,
		     "younow_get_ingest: curl_easy_perform() failed: %s",
		     curl_easy_strerror(res));
		curl_easy_cleanup(curl_handle);
		free(chunk.memory);
		return server;
	}

	curl_easy_getinfo(curl_handle, CURLINFO_RESPONSE_CODE, &response_code);
	if (response_code != 200) {
		blog(LOG_WARNING,
		     "younow_get_ingest: curl_easy_perform() returned code: %ld",
		     response_code);
		curl_easy_cleanup(curl_handle);
		free(chunk.memory);
		return server;
	}

	curl_easy_cleanup(curl_handle);

	if (chunk.size == 0) {
		blog(LOG_WARNING,
		     "younow_get_ingest: curl_easy_perform() returned empty response");
		free(chunk.memory);
		return server;
	}

	if (current_ingest) {
		free(current_ingest);
		current_ingest = NULL;
	}

	current_ingest = strdup(chunk.memory);
	free(chunk.memory);
	blog(LOG_INFO, "younow_get_ingest: returning ingest: %s",
	     current_ingest);
	return current_ingest;
}