__attribute__((used)) static void trace_print_header(int seq, int prefix)
{
	printf("%*s[%d]: ", prefix, "", seq);
}